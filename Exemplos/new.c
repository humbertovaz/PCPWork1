void relax_jacobi (double *g2, double *g1, unsigned sizex, unsigned sizey)
{
	double diff, sum=0.0;
	int nbx, bx, nby, by;

	nbx = omp_get_max_threads();			// NR de threads 
	bx = sizex/nbx + ((sizex%nbx) ? 1 : 0); // chunksize de cada linha  -> cada thread fica responsável por um chunk 
	nby = 2; 								// Nr de chunks por thread 					
	by = sizey/nby;							// chunksize em cada coluna

	#pragma omp parallel for reduction//(+:sum) private(diff)
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