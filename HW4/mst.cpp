//============================================================================
// Name        : mst.cpp
// Author      : Abdullah Saydemir
// Version     : 1.8
// Copyright   : BSD
// Date        : May 16, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of Prim's algorithm using adjacency 
//				 matrix. Uses a Graph struct to store nodes, adjacency matrix and   
//               MST. Main reads nodes from graph.txt, calculates the distances 
//               between each pair of nodes and updates the adjacency matrix. Then,
//               MST and its length are calculated. Main outputs the test case and
//				 the length of MST.
//============================================================================

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;

struct Graph
{
	vector<tuple<int,int>> nodes;
	vector<vector<int>> adj_matrix;

	int numnodes = 0;
	int mst_length = 0;

	Graph(int numnodes) : numnodes(numnodes) 
	{
		adj_matrix  = vector< vector<int> >(numnodes,vector< int >(numnodes,0));         // adjacency matrix, all values are initially 0
		nodes       = vector< tuple< int,int > >();                                      // points in the graph
		
		// below structures are to be while used finding MST
		is_included = vector< bool >(numnodes,false);                                    // specifies if that vertex is included in MST
		mst_keys    = vector< int >(numnodes,INT_MAX);                                   // can be initialized in function find_mst
		parent      = vector< int >(numnodes,0);										 // parent of a node in MST
	}

	// this function calculates the distances between each
	// pair of vertices and updates the adjacency matrix
	void calculate_weights() 
	{

		for (auto i = 0; i < nodes.size()-1 ; ++i) 
		{
			// get first pair
			auto x1 = get<0>(nodes[i]);
			auto y1 = get<1>(nodes[i]);

			for (auto j = i+1; j < nodes.size(); ++j)
			{
				// get second pair 
				auto x2 = get<0>(nodes[j]);
				auto y2 = get<1>(nodes[j]);

				// calculate the distance & update
				auto d = nearest_int(x1,y1,x2,y2);
				adj_matrix[i][j] = d;
				adj_matrix[j][i] = d;
			}
		}
	}

	void find_mst()
	{
		mst_keys[0] = 0;
		parent[0] = -1;

		// for each vertex find the closest vertex that can
		// be included to the MST.
		for (int i = 0; i < numnodes - 1; ++i)
		{
			auto u = find_min_edge();
			is_included[u] = true;


			// after a vertex is included to the MST
			// for each vertex that is adjacent to that vertex
			// update the key values and the parent.
			for (int v = 0; v < numnodes; ++v)
			{
				//   u-v is adjacent &&    not in MST   && cost of that edge is less than the key
				if (adj_matrix[u][v] && !is_included[v] && adj_matrix[u][v] < mst_keys[v] ) 
				{
					mst_keys[v] = adj_matrix[u][v];
					parent[v] = u;
				}
			}
		}
		// we have the MST, calculate the length
		calculate_mst_length();
	}

	// utility function to print adjacency matrix
	// not required in HW but useful for debugging
	void print() const
	{
		for (int i = 0; i < numnodes; ++i)
		{
			for (int j = 0; j < numnodes; ++j)
			{
				cout << adj_matrix[i][j] << " ";
			}
			cout << endl;
		}
	}


private:

	// these will not be accessed outside the class
	vector<bool> is_included;
	vector<int> mst_keys;
	vector<int> parent;

	// calculate the distance between two points and
	// round it to the nearest integer
	int nearest_int(int x1, int y1, int x2, int y2)
	{
		return round(sqrt((x1 - x2)*(x1 - x2) + (y1-y2) * (y1-y2)));
	}

	// function to find the minimum edge in the graph
	// that ties an unincluded vertex to MST. Other than
	// that, this is a classic function that returns the
	// index of the minimum element in an array.
	int find_min_edge() const
	{
		auto min = INT_MAX;
		auto index = -1;

		for (int i = 0; i < numnodes; ++i)
		{
			if ( !is_included[i] && mst_keys[i] < min) 
			{
				min = mst_keys[i];
				index = i;
			}
		}
		return index;
	}

	// this function uses tree structure to calculate the
	// length of MST. For each node, the distance between
	// its parent is added to sum.
	void calculate_mst_length() 
	{
		for (int i = 1; i < numnodes; ++i)
		{
			mst_length += adj_matrix[i][parent[i]];
		}
	}
};

int main() 
{
    string testfile = "graph.txt";                       // Test file is always "graph.txt". No need for argv
    ifstream file(testfile.c_str());

    if (file.is_open())                                    // Check if the file is correctly opened.
    {
        cin.rdbuf(file.rdbuf());
    }
    else {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    // read how many test cases are there
	auto num_tests = 0;
	cin >> num_tests;

	auto numV = 0;
	
	// for each test case
	for (int i = 0; i < num_tests ; ++i) 
	{
		
		// read how many vertices we will have
		// and initialize the graph
		cin >> numV;
		auto graph = Graph(numV);

		auto x = 0;
		auto y = 0;
		
		// read all the points line by line and
		// store them in the graph
		for (int j = 0; j < numV; ++j)
		{
			cin >> x;
			cin >> y;
			graph.nodes.push_back(make_tuple(x,y));
		}

		// calculate the weights of all edges
		graph.calculate_weights();

		// find the MST and get the length of it
		graph.find_mst();
		int lenght = graph.mst_length;


		// Print the result
		cout << "Test case " << i+1 << ": MST weight " << lenght << endl << endl;
		//graph.print();


		// C++ uses automatic destruction for structs
	}
}