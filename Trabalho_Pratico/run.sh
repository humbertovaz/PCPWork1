#!/bin/sh

module load gcc/5.3.0

echo "Compiling..."

#export SEQUENTIAL=yes
#export PARALLEL=yes

gcc PCP/PCPWork1/Trabalho_Pratico/src/calor.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o PCP/PCPWork1/Trabalho_Pratico/src/calor

echo "Running the tests"

./PCP/PCPWork1/Trabalho_Pratico/src/calor


