#include <stdio.h>
#include <time.h>
#define SIZE 1500
double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
int main(){
	clock_t start, end;
	float seconds;
	register double f;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			A[i][j]=1.1;
			B[i][j]=1.1;
		}
	}
	start = clock();
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++){
			f=0;
			for (int k=0; k<SIZE; k++)
				f += A[i][k] * B[k][j];
			C[i][j] = f;
		}

	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;

	//printf("%f", C[1200][1200]);
    printf("%.2lf sec\n",seconds);

	return 0;
}
