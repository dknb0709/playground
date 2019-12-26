#!/bin/bash

# ----------------------------------------------------
# calc fib(n) where n in $1 to $2
# $3: switch implementation
#   -DV1, -DV2, -DV3
# ----------------------------------------------------

ROOT=$(pwd)
OPTIMIZE=-O6
PROGRAM=fib

if [ $# -ne 3 ]; then
  echo "[Error] invalid arguments"
  echo "  example: ./fib.sh 30 40 -DV1"
  exit 1
fi

g++ $ROOT/fibonacci.cpp -o fib $OPTIMIZE $3

for i in $(seq $1 $2); do
  $ROOT/fib $i
done

