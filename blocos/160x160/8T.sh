#!/bin/bash
export ITER=1
export LINES=160
export COLLUMNS=160
module load gcc/4.9.0
cd PCPWork1
gcc Trabalho_Pratico/src/heatplate.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o Trabalho_Pratico/bin/heatplate

######################## SEQUENCIAL ########################
#export MODE=1 
#echo "SEQUENTIAL NORMAL:" 
#n=5
#while [ $n -gt 0 ]
#do
#    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
#    (( n-- ))
#done

######################## SEQUENCIAL COM SWAP ##################
#export MODE=5
#echo "SEQUENCIAL COM SWAP"
#
#n=5
#while [ $n -gt 0 ]
#do
#    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
#   (( n-- ))
#done

####################### PARALELO COM SWAP ####################

export MODE=5
export OMP_NUM_THREADS=8
echo "8 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done
