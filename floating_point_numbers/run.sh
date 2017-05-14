#!/bin/bash

make clean; clear;

echo "------------"

echo "Compiling program..."
make || exit

echo "Running program..."
echo "------------"

./floating_point_numbers

