//============================================================================
// Name        : tsp.cpp
// Author      : Abdullah Saydemir
// Version     : 1.13
// Copyright   : BSD
// Date        : June 3, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of nearest neighbor TSP algorithm   
//               using adjacency matrix. Uses a Graph struct to store nodes,     
//               adjacency matrix and TSP path. Main reads nodes from argument   
//               vector, calculates the distances between each pair of nodes and 
//               updates the adjacency matrix. Then, TSP path and its length are 
//               calculated.
//============================================================================

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
    int distance   = 0;

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

    // this function calculates the distance of 
    // approximated TSP path and the cities
    auto tsp(int start)                        -> void
    {
        // start is also used as the index of the latest included node
        visited_nodes.push_back(start);

        auto min_dist = 0;                  // minimum distance to a node from the current node    
        auto index = 1;                     // index of the next node salesman visit


        // Graph has num_cities node. Starting node is
        // included. Therefore, we will visit num_cities -1
        // nodes
        for (auto i = 0; i < num_cities-1; ++i) 
        {
            min_dist = INT_MAX;

            // for all adjacent nodes
            for (auto j = 0; j < num_cities; ++j) 
            {   
                if ( !is_visited(j) && adj_matrix[start][j] < min_dist) 
                {
                    min_dist = adj_matrix[start][j];
                    index = j;
                }
            }

            distance += min_dist;               // include the last path traveled
            visited_nodes.push_back(index);     // include the visited node to the path
            start = index;                      // update the current index
        }

        // add the distance between the last 
        // visited node and the starting node
        distance += adj_matrix[visited_nodes.back()][visited_nodes[0]];  
    }

    // print the distance and path to
    // the given filename
    auto print_results(string& filename)     -> void
    {
        ofstream out;

        out.open(filename, ios::trunc);         // open file, if exist write on it

        out << distance << endl;                // print distance to the first line

        for (int item : visited_nodes) 
        {
            out << item << endl;                // print each city line by line
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
    auto nearest_int(int x1, int y1, int x2, int y2)         -> int
    {
        return round(sqrt((x1 - x2)*(x1 - x2) + (y1-y2) * (y1-y2)));
    }

    // returns if given city is in the TSP path or not
    auto is_visited(int i)                                  -> bool
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
    else 
    {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    string output_file = argv[1];
    output_file.append(".tour");
    
    auto num_cities = 0;                                    // how many nodes in the graph
    cin >> num_cities;

    auto graph = Graph{num_cities};

    // take points representing the vertices and put them into the graph
    for (auto i = 0; i < num_cities; ++i) 
    {
        auto id = 0;
        auto  x = 0;
        auto  y = 0;

        cin >> id >> x >> y;

        graph.nodes.push_back(make_tuple(id,x,y));
    }

    // calculate weights of all edges
    graph.calculate_weights();
    //graph.print_matrix();

    // choose a “random” integer and run the tsp algorithm
    auto start = rand() % num_cities;
    //cout << "Starting node: " << start << endl;
    graph.tsp(start);

    // print the distance and the path to the file
    graph.print_results(output_file);

    return 0;
}