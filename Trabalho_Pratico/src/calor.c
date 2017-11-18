#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
#define M 1000
#define N 1000
#define ITER 50
double G1[N][N];
double G2[N][N];
double wtime=0;


//int NMAXTHREADS=omp_get_max_threads();

long long unsigned initial_time;
double clearcache [30000000];

void clearCache (void) {
	for (unsigned i = 0; i < 30000000; ++i)
		clearcache[i] = i;
}

void fillMatrix(){
    int i,j;
    #pragma omp parallel shared (G2) private (i,j)
    {
        #pragma omp for
            for ( i = 1; i < M - 1; i++ ){
                G2[i][0] = 100.0;
            }
        #pragma omp for
            for ( i = 1; i < M - 1; i++ ){
                G2[i][N-1] = 100.0;
            }
        #pragma omp for
            for ( j = 0; j < N; j++ ){
                G2[M-1][j] = 100.0;
            }
        #pragma omp for
            for ( j = 0; j < N; j++ ){
                G2[0][j] = 0.0;
            }
        #pragma omp for 
            for ( i=1; i< M - 2; i++)
                for( j=1; j< N - 2; j++){
                    G2[i][j] = 0.0;
                }
    }
}
double iterationSequential(){
    int iter=0;
    double aux[M];
    wtime = omp_get_wtime ();
    while (iter < ITER){
        for(int i=1; i<N-1; i++){ 
            aux = G2[i];
            for(int j=1; j<M-1; j++){
                G1[i][j]=0.2*( 
                    G2[i-1][j]+
                    G2[i+1][j]+
                    aux[j-1]+
                    aux[j+1]+
                    aux[j]);
            }   
        }
        memcpy(G1,G2,N*M*sizeof(double));
                
    ++iter;
    }
return (omp_get_wtime() - wtime); 
}
double iterationBlocks(){
int nbx, bx, nby, by;
  nbx = omp_get_max_threads();      // NR de threads 
  bx = M/nbx + ((M%nbx) ? 1 : 0);   // linha do bloco (quantas linhas fica cada bloco)
  nby = nbx;                        // Nr de chunks por thread          
  by = N/nby;                       // coluna do bloco (quantas tem cada bloco)
  int iter=0;
  wtime = omp_get_wtime();
  
    while(iter<ITER){
        #pragma omp parallel for  //reduction(+:sum) private(diff) //  i -> linhas; j colunas; ii-> chunk atual de linhas; jj-> chunk atual  de colunas
        for (int ii=0; ii<nbx; ii++)  // Criar #nbx threads    
            for (int jj=0; jj<nby; jj++)   // Limitar chunksize por thread
                for (int i=1+ii*bx; i<=min((ii+1)*bx, M-2); i++)       // cada i é uma linha do bloco
                    for (int j=1+jj*by; j<=min((jj+1)*by, N-2); j++) {    // cada j é uma coluna do bloco
                    G1[i][j]= 0.2 * (G2[i][j]+ //itself  
                                    G2[i][j-1]+  // left
                                    G2[i][j+1]+  // right
                                    G2[(i-1)][j]+  // top
                                    G2[(i+1)][j]); // bottom
                    }
                //Copiar de volta para a Memória
            #pragma omp parallel for
            for(int i=0; i<N;++i)
                for(int j=0;j<M;++j)
                    G2[i][j]=G1[i][j];

    ++iter;
    }
return (omp_get_wtime() - wtime);
}
double iterationParallel(){
    int iter=0;
    double aux[M]
    wtime = omp_get_wtime ();
    while (iter < ITER){
        #pragma omp parallel for num_threads(omp_get_max_threads()) private(aux)
        for(int i=1; i<N-1; ++i){ 
            aux = G2[i];
            for(int j=1; j<M-1; ++j){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    aux[j-1]+
                    aux[j+1]+
                    aux[j]);
            }
        }
    
    
    //Copy the G1 array calculated values back to the G2 array -> MEMCOPY
        #pragma omp parallel for
        for(int i=0; i<N;++i){
            aux = G1[i];
            for(int j=0;j<M;++j)
                G2[i][j]=aux[j];
        }
        //memcpy(G1,G2,N*M*sizeof(double));
    ++iter;
    }
return (omp_get_wtime () - wtime);   
}
int main(int argc, char const *argv[]){
    //printf("Matrix Size: %f bytes",M*N*sizeof(double));
    int sequential=1,parallel=1,blocks=1;
    //clock_t start_t, end_t, total_t;
    //start_t=omp_get_wtime();
    double start,end,total;
//#ifdef D_SEQUENTIAL
if (sequential==1){
    clearCache();
    fillMatrix();
    total=iterationSequential();
    printf("SEQUENTIAL-Total time taken by CPU: %f\n", total  );
}
    //#endif 
//#ifdef D_PARALLEL
if (parallel==1){
    clearCache();
    fillMatrix();
    total=iterationParallel();
    printf("PARALLEL- Total time taken by CPU: %f\n", total);
}
    //#endif
if (blocks==1){
    clearCache();
    fillMatrix();
    total=iterationBlocks();
    printf("PARALLEL w/ Blocks- Total time taken by CPU: %f\n", total);
}
    printf("Done!\n");
}