#include <stdio.h>
#include <time.h>
#define SIZE 1500
#define BLOCK_SIZE 50
void split_matrix(int, int, int, int);
double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
int main(){
	clock_t start, end;
	float seconds;

	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			A[i][j]=1.1;
			B[i][j]=1.1;
		}
	}
	start = clock();
	for(int i=1;i<=SIZE/BLOCK_SIZE;i++){
		for(int j=1;j<=SIZE/BLOCK_SIZE;j++){
			for(int k=1;k<=SIZE/BLOCK_SIZE;k++){
				split_matrix(i, j, j, k);
			}
		}
	}
	
	/*for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printf("C [%d][%d]: %f\n",i,j, C[i][j]);
		}
	}*/
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;

	//printf("%f", c[1200][1200]);
    printf("%.2lf sec\n",seconds);

}

void split_matrix(int Abx, int Aby, int Bbx, int Bby){
	double a[BLOCK_SIZE][BLOCK_SIZE];
	double b[BLOCK_SIZE][BLOCK_SIZE];
	double c[BLOCK_SIZE][BLOCK_SIZE];
	register int an=0;
	register int bn=0;
	register int cn=0;
	register int am=0;
	register int bm=0;
	register int cm=0;
	double V[BLOCK_SIZE];
	register double f;
	for(int i=(Abx-1)*BLOCK_SIZE;i<Abx*BLOCK_SIZE;i++){
		am=0;
		for(int j=(Aby-1)*BLOCK_SIZE;j<Aby*BLOCK_SIZE;j++){
			a[an][am]=A[i][j];
			am++;
		}
		an++;
	}//generate A(Abx,Aby)

	for(int i=(Bbx-1)*BLOCK_SIZE;i<Bbx*BLOCK_SIZE;i++){
		bm=0;
		for(int j=(Bby-1)*BLOCK_SIZE;j<Bby*BLOCK_SIZE;j++){
			b[bn][bm]=B[i][j];
			bm++;
		}
		bn++;
	}//generate B(Bbx,Bby)

	for (int i=0; i<BLOCK_SIZE; i++){
		for(int p=0;p<BLOCK_SIZE;p++){
			V[p] = b[p][i];
		}
		register double * ptr = &a[0][0];
		for (int k=0; k<BLOCK_SIZE; k++)
		{
			f = 0;
			for (int j=0; j<BLOCK_SIZE; j++){
				//f += a[k][j] * V[j];
				f += *ptr * V[j];
			   	ptr++;	
			}
			c[k][i] = f;
		}
	}//generate A(Abx,Aby)*B(Bbx,Bby)

	/*for(int i=0;i<block_size;i++){
		for(int j=0;j<block_size;j++){
			printf("A(%d,%d)*B(%d, %d) [%d][%d]: %f\n", Abx, Aby, Bbx, Bby, i,j, c[i][j]);
		}
	}*/
	for(int i=(Abx-1)*BLOCK_SIZE;i<Abx*BLOCK_SIZE;i++){
		cm=0;
		for(int j=(Bby-1)*BLOCK_SIZE;j<Bby*BLOCK_SIZE;j++){
			C[i][j]+=c[cn][cm];
			cm++;
			//printf("C(%d, %d)%f\n", i, j, C[i][j]);
		}
		cn++;
	}

}

