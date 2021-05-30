import sys

i = int(sys.argv[1])
tsp_optimal = [14, 108159, 2579, 5333, 7411, 23001]
filename = "tsp_example_" + str(i) + ".txt.tour"
f = open(filename, "r")
mysolution = int(f.readline())
print("Optimal solution : " + str(tsp_optimal[i]))
print("Approximation ratio " + str(mysolution / tsp_optimal[i]) + "\n" )
f.close()