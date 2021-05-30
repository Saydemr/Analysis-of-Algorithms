import os


cmd = "g++-10 tsp.cpp -o tsp -lm -std=c++20"
os.system(cmd)

for t in [0,1,2,3,4,5]:
	input_filename = "tsp_example_" + str(t) + ".txt"
	solution_filename = input_filename + ".tour"

	cmd = "./tsp " + input_filename
	os.system(cmd)

	cmd = "python tsp-verifier.py " + input_filename + " " + solution_filename

