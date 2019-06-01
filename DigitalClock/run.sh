#!/bin/bash

ROOT=$(pwd)

g++ $ROOT/main.cpp -o $ROOT/main.out -O6
clear
$ROOT/main.out

