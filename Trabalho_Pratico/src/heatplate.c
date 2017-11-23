#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
double total;
int mode,ITER,N,M;
double **G1;
double **G2;
double tempo;
double wtime=0;
double clearcache [30000000];

void clearCache (void) {
	for (unsigned i = 0; i < 30000000; ++i)
		clearcache[i] = i;
}

void fillMatrix(){
    int i,j;
    #pragma omp parallel shared (G2) private (i,j)
    {
        //CIMA
        #pragma omp for
            for ( i = 0; i < M ; i++ ){
                G2[0][i] = 100;
                G1[0][i] = 100;
            }
        //BAIXO
        #pragma omp for
            for ( i = 0; i < M ; i++ ){
                G2[N-1][i] = 100;
                G1[N-1][i] = 100;
            }
        //ESQUERDA
        #pragma omp for
            for ( i = 1; i < N-1 ; i++ ){
                G2[i][0] = 100;
                G1[i][0] = 100;
            }
        //DIREITA    
        #pragma omp for
            for ( i = 1; i < N -1 ; i++ ){
                G2[i][M-1] = 100;
                G1[i][M-1] = 100;
            }
        //RESTA    
        #pragma omp for 
            for ( i=1; i < N - 1 ; i++)
                for( j=1; j< M - 1 ; j++){
                    G2[i][j] = 0;
                }
    }
}
void iterationSequentialCopIter(){
    int iter=0;
    while (iter < ITER){
        for(int i=1; i<N-1; i++){ 
            for(int j=1; j<M-1; j++){
                G1[i][j] = 0.2*(
                            G2[i-1][j]+
                            G2[i+1][j]+
                            G2[i][j-1]+
                            G2[i][j+1]+
                            G2[i][j]);
            }   
        }
        ++iter;

        for(int i=1; i<N-1;++i)
            for(int j=1;j<M-1;++j)
                G2[i][j]=G1[i][j];          

    }              
}
void iterationSequentialCopSwap(){
    int iter=0;
    double** temp;
    while (iter < ITER){
        for(int i=1; i<N-1; i++){ 
            for(int j=1; j<M-1; j++){
                G1[i][j] = 0.2*(
                            G2[i-1][j]+
                            G2[i+1][j]+
                            G2[i][j-1]+
                            G2[i][j+1]+
                            G2[i][j]);
            }   
        }
    ++iter;
    temp = G2;
    G2 = G1;
    G1 = temp;
    }              
}
void iterationSequentialCopMem(){
    int iter=0;
    while (iter < ITER){
        for(int i=1; i<N-1; i++){ 
            for(int j=1; j<M-1; j++){
                G1[i][j] = 0.2*(
                            G2[i-1][j]+
                            G2[i+1][j]+
                            G2[i][j-1]+
                            G2[i][j+1]+
                            G2[i][j]);
            }   
        }
        ++iter;          
        memcpy(G2,G1,sizeof(double)*N*M);
    }              
}

void swapBlocks(){
int nbx, bx, nby, by;
  nbx = omp_get_max_threads();      // NR de threads 
  nbx=2;
  bx = M/nbx + ((M%nbx) ? 1 : 0);   // linha do bloco (quantas linhas fica cada bloco)
  nby = nbx;                        // Nr de chunks por thread          
  by = N/nby + ((N%nby) ? 1 : 0);                       // coluna do bloco (quantas tem cada bloco)
  int iter=0;
  wtime = omp_get_wtime();
  int i,j,ii,jj;
  double** temp;
    while(iter<ITER){
        #pragma omp parallel for  
        for (ii=0; ii<nbx; ii++)  // Criar #nbx threads    
            for (jj=0; jj<nby; jj++)   // Limitar chunksize por thread
                for (i=1+ii*bx; i<=min((ii+1)*bx, M-2); i++)       // cada i é uma linha do bloco
                    for (j=1+jj*by; j<=min((jj+1)*by, N-2); j++) {    // cada j é uma coluna do bloco
                         G1[i][j]=0.2*( 
                            G2[i-1][j]+
                            G2[i+1][j]+
                            G2[i][j-1]+
                            G2[i][j+1]+
                            G2[i][j]);
            }   
                //Copiar de volta para a Memória
      temp = G2;
    G2 = G1;
    G1 = temp;
    ++iter;
  }
      
}


void iterationParallel(){
    int iter=0;
    while (iter < ITER){
        wtime = omp_get_wtime ();
        #pragma omp parallel for
        for(int i=1; i<N-1; ++i){ 
            for(int j=1; j<M-1; ++j){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }
        }
        //Copiar de volta para a Memória
            #pragma omp parallel for
            for(int i=1; i<N-1;++i){
                    for(int j=1;j<M-1;++j)
                        G2[i][j]=G1[i][j];          
            }
    ++iter;
    }
            for(int i=0; i<N;++i){
                for(int j=0;j<M;++j){
                 printf(" %lf ", G2[i][j]);   
                }
                printf("\n");
            }
}
void init(){
    G1 = (double **) malloc(N*sizeof(double));
    G2 = (double **) malloc(N*sizeof(double));
    for(int i = 0; i < N; i++){
        G1[i] = (double *) malloc(M*sizeof(double));
        G2[i] = (double *) malloc(M*sizeof(double));
    }
}
int main(int argc, char* argv []){
    if(argc>1){
        mode = atoi(argv[1]);
        ITER= atoi(argv[2]);
        N = atoi(argv[3]);
        M = atoi(argv[4]);
        init();
        clearCache();
        fillMatrix();
        if(mode==1){
            tempo = omp_get_wtime ();
            iterationSequentialCopIter();
            tempo = omp_get_wtime () - tempo;
            printf("Tempo SEQUENTIAL NORMAL: %lf \n",tempo);
        }
        else if (mode==2){
            tempo = omp_get_wtime ();
            iterationSequentialCopSwap();
            tempo = omp_get_wtime () - tempo;
            printf("Tempo SEQUENTIAL W/SWAP: %lf \n",tempo);
        }
        else if (mode == 3){
            tempo = omp_get_wtime ();
            swapBlocks();
            tempo = omp_get_wtime () - tempo;
            printf("Tempo SWAP BLOCKS: %lf \n",tempo);
        }
    }
return 0;
}

