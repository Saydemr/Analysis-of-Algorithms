//============================================================================
// Name        : mergeTime.cpp
// Author      : Abdullah Saydemir
// Version     : 1.4
// Copyright   : BSD
// Date        : March 9, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : This program directly copies insertion_sort() algorithm from    
//               insertsort.cpp and uses it to measure running times for 10  
//               different sizes of vectors.
//============================================================================


#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;
auto N = 5000; // This is the size of the minimum array to be sorted.

// copy of insertion sort from insertsort.cpp
void insertion_sort(vector<int>& to_sort)
{
    for (auto i = 1; i < to_sort.size() ; ++i)
    {
        auto pivot = to_sort[i];
        auto j = i;

        while (j > 0 && to_sort[j-1] > pivot)
        {
            to_sort[j] = to_sort[j-1];
            j = j-1;
        }
        to_sort[j] = pivot;
    }
}

int main()
{
	// This code is to get uniformly distributed random integers. srand() and rand() functions do not give uniform results.
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0,10000);

    cout << "   Size (n)       Time (ms)" << endl;
    for (auto i = N; i <= N*10 ; i+= N)
    {
        auto total_time_elapsed = 0.0;

        for (auto attempts = 0; attempts < 3 ; ++attempts) // to smooth the running time
        {
            auto to_sort = vector<int>();

            // put random integers to vector
            for (auto j = 0; j < i ; ++j)
            {
                to_sort.push_back(uni(rng));
            }
			
			auto start = chrono::steady_clock::now();
    		insertion_sort(to_sort);
    		auto end = chrono::steady_clock::now();

            auto time = chrono::duration_cast<chrono::microseconds>(end - start).count(); // in microseconds
			total_time_elapsed += time; // just add up, average is calculated later
            
            to_sort.clear();
        }
        cout << "    " <<  i << "          " << total_time_elapsed / 1000.0f / 3.0f  << endl;
    }
}
