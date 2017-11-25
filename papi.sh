#!/bin/bash
export ITER=1
export LINES=160
export COLLUMNS=160
module load gcc/4.9.0
module load papi/5.5.0
cd PCPWork1
gcc Trabalho_Pratico/src/heatplatePapi.c -O3-L /share/apps/papi/5.5.0/lib/ -fopenmp -lpapi -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o Trabalho_Pratico/bin/testePapiSeq

######################## SEQUENCIAL ########################
export MODE=1 
echo "SEQUENTIAL NORMAL:" 
n=5
while [ $n -gt 0 ]
do
    ./testePapiSeq $MODE $ITER $LINES $COLLUMNS
    (( n-- ))
done

######################## SEQUENCIAL COM SWAP ##################
export MODE=2
echo "SEQUENCIAL COM SWAP"
n=5
while [ $n -gt 0 ]
do
    ./testePapiSeq $MODE $ITER $LINES $COLLUMNS
   (( n-- ))
done

####################  ITerativo  ###################
export MODE=3
echo "ITERATIVO COPIA"
n=5
while [ $n -gt 0 ]
do
    ./testePapiSeq $MODE $ITER $LINES $COLLUMNS
   (( n-- ))
done
####################  ITerativo SWAP  ###################
export MODE=4
echo "ITERATIVO SWAP"
n=5
while [ $n -gt 0 ]
do
    ./testePapiSeq $MODE $ITER $LINES $COLLUMNS
   (( n-- ))
done
