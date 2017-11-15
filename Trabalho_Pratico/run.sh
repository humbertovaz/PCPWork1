#!/bin/sh

echo "Compiling..."

#export SEQUENTIAL=yes
#export PARALLEL=yes

gcc src/calor.c -O3 -fopenmp -Wall -Wextra -std=c99 -Wno-unused-parameter -o src/calor

echo "Running the tests"

./src/calor


