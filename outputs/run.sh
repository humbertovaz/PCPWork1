#!/bin/sh

# Mode 1 -> Sequential ITER; Mode 2 COSWAP; Mode 3 CopMem

module load gcc/5.3.0

echo "Running.."

echo "A compilar ficheiros.."

cd /home/a73236/PCP/PCPWork1/
gcc Trabalho_Pratico/src/heatplate.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o /home/a73236/PCP/PCPWork1/Trabalho_Pratico/bin/heatplate

echo "A correr "

cd Trabalho_Pratico/bin
            #$MODE $ITER $THREADS $LINES $COLLUMNS        


echo ""
./heatplate 1 1 1 10000 10000
echo ""
./heatplate 1 1 1 20000 20000
echo ""
./heatplate 1 1 1 30000 30000
echo ""
./heatplate 1 1 1 40000 40000
echo ""
./heatplate 1 1 1 50000 50000

 
