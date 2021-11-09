#include <stdio.h>
#include <time.h>
#define SIZE 1500
double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
int main(){
	register double f;
	clock_t start, end;
	float seconds;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			A[i][j]=1.1;
			B[i][j]=1.1;
		}
	}
	start = clock();
	for (int i=0; i<SIZE; i++)
		for (int k=0; k<SIZE; k++)
		{
			f = A[i][k];
			for (int j=0; j<SIZE; j++)
				C[i][j] += f * B[k][j];
		}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;

	//printf("%f", c[1200][1200]);
    printf("%.2lf sec\n",seconds);

	return 0;
}

