#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
double total;
int mode,ITER,THREADS,N,M;
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
            }
        //BAIXO
        #pragma omp for
            for ( i = 0; i < M ; i++ ){
                G2[N-1][i] = 100;
            }
        //ESQUERDA
        #pragma omp for
            for ( i = 1; i < N-1 ; i++ ){
                G2[i][0] = 100;
            }
        //DIREITA    
        #pragma omp for
            for ( i = 1; i < N -1 ; i++ ){
                G2[i][M-1] = 100;
            }
        //RESTA    
        #pragma omp for 
            for ( i=1; i < N - 1 ; i++)
                for( j=1; j< M - 1 ; j++){
                    G2[i][j] = 0;
                }
    }
}
double iterationSequential(){
    int iter=0;
    double *aux;
    double acum=0;
    while (iter < ITER){
        wtime = omp_get_wtime ();
        for(int i=1; i<N-1; i++){ 
            aux = G2[i];
            for(int j=1; j<M-1; j++){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    aux[j-1]+
                    aux[j+1]+
                    aux[j]);
            }   
        }
        acum += omp_get_wtime() - wtime;
        ++iter;
        // Tentar com memcpy
        for(int i=1; i<N-1;++i)
            for(int j=1;j<M-1;++j)
                G2[i][j]=G1[i][j];          

    }
            for(int i=0; i<N;++i){
                for(int j=0;j<M;++j){
                 printf(" %lf ", G2[i][j]);   
                }
                printf("\n");
            }
                 
return acum; 
}
double iterationBlocks(){
int nbx, bx, nby, by;
  nbx = THREADS;      // NR de threads 
  bx = M/nbx + ((M%nbx) ? 1 : 0);   // linha do bloco (quantas linhas fica cada bloco)
  nby = nbx;                        // Nr de chunks por thread          
  by = N/nby;                       // coluna do bloco (quantas tem cada bloco)
  int iter=0;
  double acum=0;
  double *aux;
    while(iter<ITER){
        wtime = omp_get_wtime ();
        #pragma omp parallel for  //reduction(+:sum) private(diff) //  i -> linhas; j colunas; ii-> chunk atual de linhas; jj-> chunk atual  de colunas
        for (int ii=0; ii<nbx; ii++){  // Criar #nbx threads    
            for (int jj=0; jj<nby; jj++){   // Limitar chunksize por thread
                for (int i=1+ii*bx; i<=min((ii+1)*bx, M-2); i++){       // cada i é uma linha do bloco
                   aux = G2[i];
                    for (int j=1+jj*by; j<=min((jj+1)*by, N-2); j++) {    // cada j é uma coluna do bloco
                         G1[i][j]=0.2*( 
                            G2[i-1][j]+
                            G2[i+1][j]+
                            aux[j-1]+
                            aux[j+1]+
                            aux[j]);
                    }
                }
            }
        }
            acum += omp_get_wtime() - wtime;
            ++iter;
    }  
           
            //Copiar de volta para a Memória
            #pragma omp parallel for
            for(int i=1; i<N-1;++i){
                    for(int j=1;j<M-1;++j)
                        G2[i][j]=G1[i][j];          
            }
            for(int i=0; i<N;++i){
                for(int j=0;j<M;++j){
                 printf(" %lf ", G2[i][j]);   
                }
                printf("\n");
            }

return acum;
}
double iterationParallel(){
    int iter=0;
    double *aux;
    double acum=0;
    while (iter < ITER){
        wtime = omp_get_wtime ();
        #pragma omp parallel for num_threads(THREADS) private(aux)
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
        acum+=omp_get_wtime() - wtime;
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
return acum;   
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
        THREADS =atoi(argv[3]);
        N = atoi(argv[4]);
        M = atoi(argv[5]);
        init();
        clearCache();
        fillMatrix();
        if(mode==1){
            tempo=iterationSequential();
            printf("Sequential Time: %lf \n",tempo);
        }
        else if (mode==2){
            tempo=iterationParallel();
            printf("Parallel Time: %lf \n",tempo);
        }
        else if (mode == 3){
            tempo=iterationBlocks();
            printf("Parallel w/ blocks Time: %lf \n",tempo);
        }
    }
    printf("Done!\n");
return 0;
}

