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
		adj_matrix  = vector< vector<int> >(numnodes,vector< int >(numnodes,0));
		nodes       = vector< tuple< int,int > >();
		is_included = vector< bool >(numnodes,false);
		mst_keys    = vector< int >(numnodes,INT_MAX);
		parent      = vector< int >(numnodes,0);
	}

	void calculate_weights() 
	{
		for (auto i = 0; i < nodes.size()-1 ; ++i) 
		{
			auto x1 = get<0>(nodes[i]);
			auto y1 = get<1>(nodes[i]);
			for (auto j = i+1; j < nodes.size(); ++j)
			{
				auto x2 = get<0>(nodes[j]);
				auto y2 = get<1>(nodes[j]);

				auto d = nearest_int(x1,y1,x2,y2);
				adj_matrix[i][j] = d;
				adj_matrix[j][i] = d;
			}
		}
	}

	void find_mst_edges()
	{
		mst_keys[0] = 0;
		parent[0] = -1;

		for (int i = 0; i < numnodes - 1; ++i)
		{
			auto u = find_min_edge();
			is_included[u] = true;

			for (int v = 0; v < numnodes; ++v)
			{
				if (adj_matrix[u][v] && !is_included[v] && adj_matrix[u][v] < mst_keys[v] ) 
				{
					mst_keys[v] = adj_matrix[u][v];
					parent[v] = u;
				}
			}
		}

		calculate_mst_length();
	}

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
	vector<bool> is_included;
	vector<int> mst_keys;
	vector<int> parent;

	int nearest_int(int x1, int y1, int x2, int y2)
	{
		return round(sqrt((x1 - x2)*(x1 - x2) + (y1-y2) * (y1-y2)));
	}

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

	auto num_tests = 0;
	cin >> num_tests;

	auto numV = 0;
	for (int i = 0; i < num_tests ; ++i) 
	{
		cin >> numV;
		auto graph = Graph(numV);

		auto x = 0;
		auto y = 0;
		for (int j = 0; j < numV; ++j)
		{
			cin >> x;
			cin >> y;
			graph.nodes.push_back(make_tuple(x,y));
		}

		graph.calculate_weights();
		graph.find_mst_edges();
		int lenght = graph.mst_length;

		cout << "Test case " << i+1 << ": MST weight " << lenght << endl << endl;
		//graph.print();
	}
}