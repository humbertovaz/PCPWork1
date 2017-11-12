#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10
int G1[N][N];
int G2[N][N];
long long unsigned initial_time;
double clearcache [30000000];

void clearCache (void) {
	for (unsigned i = 0; i < 30000000; ++i)
		clearcache[i] = i;
}

void fillMatrix(){
    int i,j;
    for(i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            G2[i][j]= (float) rand() / RAND_MAX;
        
    
    }
}
/*
void iteration(){
 for(int i=1; i<N-1; i++){ 
    for(int j=1; j<N-1; j++){
        G1[i][j]= (
            G2[i-1][j]+
            G2[i+1][j]+
            G2[i][j-1]+
            G2[i][j+1]+
            G2[i][j]) / 5;
    }
 }
    
}
*/

void iteration(){
 for(int i=1; i<N-1; i++){ 
    #pragma parallel for, private(aux) 
    for(int j=1; j<N-1; j++){
        int aux = (
            G2[i-1][j]+
            G2[i+1][j]+
            G2[i][j-1]+
            G2[i][j+1]+
            G2[i][j]) / 5;
            G2[i][j] = aux;
    }
asdasdas
 }
    
}
int main(int argc, char const *argv[]){
    clock_t start_t, end_t, total_t;
    
    fillMatrix ();
    //Collects the start time
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);
    // Does the job
    iteration ();
    //Collects the end time
    end_t = clock();
    // Ends the job
    printf("End of the big loop, end_t = %ld\n", end_t);
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t  );


    
}
