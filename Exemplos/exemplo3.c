
iterationParallel(){
    for(int i=1; i<N-1; i++){ 
        #pragma omp parallel for private (aux)
        for(int j=1; j<N-1; j++){
            aux = (
                G2[i-1][j]+
                G2[i+1][j]+
                G2[i][j-1]+
                G2[i][j+1]+
                G2[i][j]) / 5);
                G1[i][j] = aux;
        }

    }
    //Copy the G1 array calculated values back to the G2 array
    #pragma omp parallel for
    for(int i=0; i<N;i++){
        for(int j=0;j<N;j++)
            G2[i][j]=G1[i][j];
    }
}
