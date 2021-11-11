#include <stdio.h>
#include <time.h>
#define SIZE 1500
#define BLOCK_SIZE 50
void multiple(int, int, int, int);
void copyA(int, int);
void copyB(int, int);
double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
double va[SIZE/BLOCK_SIZE+1][BLOCK_SIZE*BLOCK_SIZE];//copy A
double vb[SIZE/BLOCK_SIZE+1][BLOCK_SIZE*BLOCK_SIZE];//copy B
int van=1;
int vbn=1;
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
		vbn=1;
		van=1;
		for(int p=1;p<=SIZE/BLOCK_SIZE;p++){
			copyB(p, i);
		}
		for(int z=1;z<=SIZE/BLOCK_SIZE;z++){
			copyA(i, z);
		}
		for(int j=1;j<=SIZE/BLOCK_SIZE;j++){
			for(int k=1;k<=SIZE/BLOCK_SIZE;k++){
				multiple(j, k, k, i);
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

	//printf("%f", C[1200][1200]);
    printf("%.2lf sec\n",seconds);

}

void multiple(int Abx, int Aby, int Bbx, int Bby){
	double a[BLOCK_SIZE][BLOCK_SIZE];
	double b[BLOCK_SIZE][BLOCK_SIZE];
	double c[BLOCK_SIZE][BLOCK_SIZE];
	register int an=0;
	register int bn=0;
	register int cn=0;
	register int am=0;
	register int bm=0;
	register int cm=0;
	register int vam=0;
	register int vbm=0;
	double V[BLOCK_SIZE];
	register double f;
	for(int i=0;i<BLOCK_SIZE;i++){
		for(int j=0;j<BLOCK_SIZE;j++){
			//printf("v[%d][%d]: %f\n", Bbx, vm, v[Bbx][vm]);
			a[i][j]=va[Abx][vam];
			vam++;
		}
	}//generate a from va
	for(int i=0;i<BLOCK_SIZE;i++){
		for(int j=0;j<BLOCK_SIZE;j++){
			//printf("v[%d][%d]: %f\n", Bbx, vm, v[Bbx][vm]);
			b[i][j]=vb[Bbx][vbm];
			vbm++;
		}
	}//generate b from vb

	/*for(int i=0;i<block_size;i++){
		for(int j=0;j<block_size;j++){
			printf("b[%d][%d]: %f\n", i, j, b[i][j]);
		}
	}
	printf("-----------------\n");*/
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
				f += *ptr*V[j];
				ptr++;
			}
			c[k][i] = f;
		}
	}//generate A(Abx,Aby)*B(Bbx,Bby)
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

void copyB(int Bbx, int Bby){
	register int z=0;
	register int bm=0;
	register double * ptr = &B[(Bbx-1)*BLOCK_SIZE][(Bby-1)*BLOCK_SIZE];
	for(int i=(Bbx-1)*BLOCK_SIZE;i<Bbx*BLOCK_SIZE;i++){
		for(int j=(Bby-1)*BLOCK_SIZE;j<Bby*BLOCK_SIZE;j++){
			//vb[vbn][z] = B[i][j];
			vb[vbn][z] = *ptr;;
			ptr++;
			z++;
		}
	}
	/*printf("Copy from B(%d, %d)\n--------------\n", Bbx, Bby);
	for(int i=0;i<block_size*block_size;i++){
		printf("v[%d][%d]: %f\n", vn, i, v[vn][i]);
	}
	printf("-----------\n");*/
	vbn++;
}
void copyA(int Abx, int Aby){
	register int z=0;
	register int bm=0;
	register double * ptr = &A[(Abx-1)*BLOCK_SIZE][(Aby-1)*BLOCK_SIZE];
	for(int i=(Abx-1)*BLOCK_SIZE;i<Abx*BLOCK_SIZE;i++){
		for(int j=(Aby-1)*BLOCK_SIZE;j<Aby*BLOCK_SIZE;j++){
			//va[van][z] = A[i][j];
			va[van][z] = *ptr;
			ptr++;
			z++;
		}
	}
	/*printf("Copy from B(%d, %d)\n--------------\n", Bbx, Bby);
	for(int i=0;i<block_size*block_size;i++){
		printf("v[%d][%d]: %f\n", vn, i, v[vn][i]);
	}
	printf("-----------\n");*/
	van++;
}

