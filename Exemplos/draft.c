

//Cruz 

#pragma omp parallel for reduction (+:linha, +:coluna)
for (int i; Percorre de cima para baixo ; ;i++){
    for (int j; Percorre da esquerda para a direita  ; j++){
        coluna += vec[k][j];
        linha  += vec[i][k];
    }
    sum [i][j] = 0.2*(linha + couluna - vec[i][j]) // -vec[i][j] retirar o elemento central da cruz repetido -> alternativa (1 if )
}