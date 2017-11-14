void iteration (double *g2, double *g1, unsigned sizex, unsigned sizey)
{
	double diff, sum=0.0;
	int nbx, bx, nby, by;

	nbx = omp_get_max_threads();			// NR de threads 
	bx = sizex/nbx + ((sizex%nbx) ? 1 : 0); // chunksize de cada linha  -> cada thread fica responsável por um chunk 
	nby = 2; 								// Nr de chunks por thread 					
	by = sizey/nby;							// chunksize em cada coluna

	#pragma omp parallel for //reduction(+:sum) private(diff)
	//  i -> linhas; j colunas; ii-> chunk atual de linhas; jj-> chunk atual  de colunas
	for (int ii=0; ii<nbx; ii++) { //Div das threads por linhas   
		for (int jj=0; jj<nby; jj++)  { // Div das threads por colunas 
			for (int i=1+ii*bx; i<=min((ii+1)*bx, sizex-2); i++) {
				for (int j=1+jj*by; j<=min((jj+1)*by, sizey-2); j++) {
					g1 [i*sizey+j]= 0.2 * ( g2[i*sizey+ j] //itself	
								   g2[ i*sizey     + (j-1) ]+  // left
					               g2[ i*sizey     + (j+1) ]+  // right
					               g2[ (i-1)*sizey	+ j     ]+  // top
					               g2[ (i+1)*sizey	+ j     ]); // bottom

				
				//	diff = utmp[i*sizey+j] - u[i*sizey + j];
				//	sum += diff * diff; 
				}
			}
		}
	}

//	return sum;
}


//faltam verificar as pontas
void interation2 (double **g2, double **g1, unsigned sizex, unsigned sizey){
#pragma omp parallel for 
for (int i=1; i< sizey-2; ;i++){
    for (int j=1; sizey-2 ; j++){
    	linha=0;
    	coluna=0;
    	#pragma omp simd reduction (+:linha, +:coluna)
    	for(int valx=i-1, int valy=j-1, a=0; a<3; a++){
        coluna += g2[valx][j];
        linha  += g2[i][valy];
    }
    sum [i][j] = 0.2*(linha + couluna - vec[i][j]) // -vec[i][j] retirar o elemento central da cruz repetido -> alternativa (1 if )
    //coluna = linha=0;
}
}