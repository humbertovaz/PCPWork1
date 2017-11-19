double iterationParallel(){
    int iter=0;
    wtime = omp_get_wtime ();
    while (iter < ITER){
        #pragma omp parallel for num_threads(omp_get_max_threads())


        //linhas superiores
        for(int i=1; i<N-1 && i <= iter+1; ++i){ //ver qual gasta menos < ou <=
            for(int j=1; j<M-1; ++j){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }

        //linhas inferiores
        for(int i=N-1-(iter+1); i<N-1 ; ++i){ 
            for(int j=1; j<M-1; ++j){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }
        }

        //colunas lado direito
        for(int j=1; j<M-1 && j <= iter+1; ++j){ //ver qual gasta menos < ou <=
            for(int i=1; i<N-1; ++i){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }
        }

        //colunas lado esquerdo

                //linhas inferiores
        for(int j=M-1-(iter+1); j<M-1; ++j){ //ver qual gasta menos < ou <=
            for(int i=1; i<N-1; ++i){
                G1[i][j] = 0.2*(
                    G2[i-1][j]+
                    G2[i+1][j]+
                    G2[i][j-1]+
                    G2[i][j+1]+
                    G2[i][j]);
            }
        }
    

    //VAI REPLICAR TRABALHO NAS PONTAS EM COMUM ENTRE LINHAS E COLUNAS FALTA RESOLVER
    
    //Copy the G1 array calculated values back to the G2 array -> MEMCOPY
        #pragma omp parallel for
        for(int i=0; i<N;++i){
            for(int j=0;j<M;++j)
                G2[i][j]=G1[i][j];
        }
        //memcpy(G1,G2,N*M*sizeof(double));
    ++iter;
    }