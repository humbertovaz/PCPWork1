#!/bin/sh

echo "Compiling..."

export SEQUENTIAL=yes
export PARALLEL=yes

make

echo "Running the tests"

./bin/calor.c


