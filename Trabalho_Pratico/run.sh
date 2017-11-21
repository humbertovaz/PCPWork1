#!/bin/sh



echo "1- Sequencial 2 - Paralelo 3 - Blocos"
read MODE
echo "NR de iteracoes: 1 10 100 1000 10000"
read ITER
echo "Insert Threads"
read THREADS
echo "Insert Lines"
read LINES
echo "Insert COLLUMNS"
read COLLUMNS

./Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS


