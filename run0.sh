#!/bin/sh
module load gcc/5.3.0

echo "Running.."

echo "A criar Pastas..."
mkdir Trabalho_Pratico/bin

echo "A compilar ficheiros.."

gcc Trabalho_Pratico/src/heatplate.c -O3 -fopenmp -Wall -Wextra -std=c99 -finline -Wno-unused-parameter -o Trabalho_Pratico/bin/heatplate
