#!/bin/sh



export ITER=2
export THREADS=1
export LINES=10
export COLLUMNS=10

# Mode 1 -> Sequential ITER; Mode 2 COSWAP; Mode 3 CopMem
export MODE=1
./Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS


export MODE=2

./Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS

export MODE=3

./Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS
