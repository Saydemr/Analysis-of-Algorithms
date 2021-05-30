#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;


struct Graph
{
	vector<tuple<int,int,int>> nodes;
	vector<vector<int>> adj_matrix;
	vector<int> visited_nodes;

	int num_cities = 0;
	int distance = 0;

	Graph(int num_cities) : num_cities(num_cities) 
	{
		adj_matrix  = vector< vector<int> >(num_cities,vector< int >(num_cities,0));         // adjacency matrix, all values are initially 0
		nodes       = vector< tuple< int,int,int > >();                                      // points in the graph
	}

	// this function calculates the distances between each
	// pair of vertices and updates the adjacency matrix
	void calculate_weights() 
	{

		for (auto i = 0; i < nodes.size()-1 ; ++i) 
		{
			// get first pair
			auto x1 = get<1>(nodes[i]);
			auto y1 = get<2>(nodes[i]);

			for (auto j = i+1; j < nodes.size(); ++j)
			{
				// get second pair 
				auto x2 = get<1>(nodes[j]);
				auto y2 = get<2>(nodes[j]);

				// calculate the distance & update
				auto d = nearest_int(x1,y1,x2,y2);
				adj_matrix[i][j] = d;
				adj_matrix[j][i] = d;
			}
		}
	}


	auto tsp(int start)                                      -> void
	{
		visited_nodes.push_back(start);

		auto min_dist = 0;
		auto index = 1;


		for (auto i = 0; i < num_cities-1; ++i) 
		{
			min_dist = INT_MAX;

			for (auto j = 0; j < num_cities; ++j) 
			{	
				if ( !is_visited(j) && adj_matrix[start][j] < min_dist) 
				{
					min_dist = adj_matrix[start][j];
					index = j;
				}
			
			}

			distance += min_dist;
			visited_nodes.push_back(index);
			start = index;

		}

		distance += adj_matrix[visited_nodes.back()][visited_nodes[0]];
	}


	auto print_results(string& filename)                                   -> void
	{
		ofstream out;

		out.open(filename, ios::trunc);

		out << distance << endl;

		for (int item : visited_nodes) 
		{
			out << item << endl;
		}

		out.close();
	}

	// utility function to print adjacency matrix
	// not required in HW but useful for debugging
	void print_matrix() const
	{
		for (int i = 0; i < num_cities; ++i)
		{
			for (int j = 0; j < num_cities; ++j)
			{
				cout << adj_matrix[i][j] << " ";
			}
			cout << endl;
		}
	}


private:

	// calculate the distance between two points and
	// round it to the nearest integer
	auto nearest_int(int x1, int y1, int x2, int y2)                                   -> int
	{
		return round(sqrt((x1 - x2)*(x1 - x2) + (y1-y2) * (y1-y2)));
	}

	auto is_visited(int i)                                                                -> bool
	{
		for (int item : visited_nodes) 
		{
			if (item == i) return true;
		}
		return false;
	}
};



int main(int argc, char const *argv[])
{
	
	string testfile = argv[1];

    ifstream file(testfile.c_str());

    if (file.is_open())                                    // Check if the file is correctly opened.
    {
        cin.rdbuf(file.rdbuf());
    }
    else {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    string outputfile = argv[1];
	outputfile.append(".tour");
	

    auto num_cities = 0;
    cin >> num_cities;

    auto graph = Graph{num_cities};

    for (auto i = 0; i < num_cities; ++i) 
    {
    	auto id = 0;
    	auto  x = 0;
    	auto  y = 0;

    	cin >> id >> x >> y;

    	graph.nodes.push_back(make_tuple(id,x,y));
    }

    graph.calculate_weights();
   // graph.print_matrix();

    auto start = rand() % num_cities;

    graph.tsp(start);
    graph.print_results(outputfile);

	return 0;
}