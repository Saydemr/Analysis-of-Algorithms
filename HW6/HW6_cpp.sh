#!/bin/bash

g++ tsp.cpp -o tsp -lm -std=c++2a

for t in 0 1 2 3 4 5 
do
	input_filename="tsp_example_$t.txt"
	solution_filename="$input_filename.tour"
	./tsp $input_filename
	python3 tsp-verifier.py $input_filename $solution_filename
	python3 approximation-verifier.py $t
done




