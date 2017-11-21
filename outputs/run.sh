#!/bin/sh



# Mode 1 -> Sequential ITER; Mode 2 COSWAP; Mode 3 CopMem
export MODE=1
export ITER=500
export THREADS=1
export LINES=10000
export COLLUMNS=10000
../Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS


export MODE=2

../Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS

export MODE=3

../Trabalho_Pratico/bin/heatplate $MODE $ITER $THREADS $LINES $COLLUMNS
