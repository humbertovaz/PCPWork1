#!/bin/bash
export ITER=1
export LINES=400000
export COLLUMNS=400000
module load gcc/4.9.0
cd PCPWork1
gcc Trabalho_Pratico/src/heatplate.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o Trabalho_Pratico/bin/heatplate

######################## SEQUENCIAL ########################
export MODE=1 
echo "SEQUENTIAL NORMAL:" 
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

######################## SEQUENCIAL COM SWAP ##################
export MODE=2
echo "SEQUENCIAL COM SWAP"

n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

####################### PARALELO COM BLOCOS ####################

export MODE=3
echo "PARALELO COM BLOCOS:"
export OMP_NUM_THREADS=2
echo "2 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

export OMP_NUM_THREADS=4
echo "4 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

export OMP_NUM_THREADS=8
echo "8 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

export OMP_NUM_THREADS=16
echo "16 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

export OMP_NUM_THREADS=32
echo "32 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

export OMP_NUM_THREADS=40
echo "40 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

echo "DONE!!"