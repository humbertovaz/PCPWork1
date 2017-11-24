#!/bin/bash
export ITER=1
export LINES=400000
export COLLUMNS=400000
module load gcc/4.9.0
cd PCPWork1
gcc Trabalho_Pratico/src/heatplate.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o Trabalho_Pratico/bin/heatplate

export OMP_NUM_THREADS=16
echo "16 Threads"
n=5
while [ $n -gt 0 ]
do
    ./Trabalho_Pratico/bin/heatplate $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done