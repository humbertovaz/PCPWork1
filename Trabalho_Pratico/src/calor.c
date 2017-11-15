#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>

#define M 500
#define N 500
#define ITER 5000
double G1[N][N];
double G2[N][N];
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
void iterationSequential(){
    int iter=0;
    while (iter < ITER){
        for(int i=1; i<N-1; i++){ 
            for(int j=1; j<M-1; j++){
                G1[i][j]=0.2*( 
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }   
        }
        //Copy the G1 array calculated values back to the G2 array -> MEMCOPY
        for(int i=0; i<N;i++){
            for(int j=0;j<M;j++)
                G2[i][j]=G1[i][j];
        }
    ++iter;
    } 
}
void iterationParallel(){
    int iter=0;
    while (iter < ITER){
        #pragma omp parallel for num_threads(8)
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
    
    
    //Copy the G1 array calculated values back to the G2 array -> MEMCOPY
        //#pragma omp parallel for
        for(int i=0; i<N;++i){
            for(int j=0;j<M;++j)
                G2[i][j]=G1[i][j];
        }
        //memcpy(&G1,&G2,N*M*sizeof(double));
    ++iter;
    }
}
int main(int argc, char const *argv[]){
    int sequential=1,parallel=1;
    //clock_t start_t, end_t, total_t;
    //start_t=omp_get_wtime();
    double start,end,total;
//#ifdef D_SEQUENTIAL
if (sequential==1){
    clearCache();
    fillMatrix ();
    //Collects the start time
    //start_t = omp_get_wtime();
    start= omp_get_wtime();
    //printf("Starting of the program, start_t = %ld\n", start_t);
    printf("SEQUENTIAL-Starting of the program, start_t = %f\n", start);
    // Does the job
    iterationSequential();
    //Collects the end time
    //end_t = omp_get_wtime();
    end=omp_get_wtime();
    // Ends the job
    //printf("End of the big loop, end_t = %ld\n", end_t);
    printf("SEQUENTIAL-End of the big loop, end_t = %f\n", end);
    //total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    total = (double)(end - start);
    //printf("Total time taken by CPU: %ld\n", total_t  );
    printf("SEQUENTIAL-Total time taken by CPU: %f\n", total  );
}
    //#endif 

//#ifdef D_PARALLEL
if (parallel==1){
    clearCache();
    fillMatrix ();
    //Collects the start time
    //start_t = clock();
    start=omp_get_wtime();
    //printf("Starting of the program, start_t = %ld\n", start_t);
    printf("PARALLEL- Starting of the program, start_t = %f\n", start);
    // Does the job
    iterationParallel();
    //Collects the end time
    //end_t = clock();
    end=omp_get_wtime();
    // Ends the job
    //printf("End of the big loop, end_t = %ld\n", end_t);
    printf("PARALLEL- End of the big loop, end_t = %f\n", end);
    //total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    total=(double)(end - start) ;
    //printf("Total time taken by CPU: %ld\n", total_t  );
    printf("PARALLEL- Total time taken by CPU: %f\n", total);
}
    //#endif
//Global Time
//end_t=omp_get_wtime();
//total_t=end_t-start_t;
//printf("Total time of both Sequential and Parallel execution:%ld\n",total_t );    


    
}