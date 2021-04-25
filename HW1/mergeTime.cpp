//============================================================================
// Name        : mergeTime.cpp
// Author      : Abdullah Saydemir
// Version     : 1.3
// Copyright   : BSD
// Date        : March 9, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : This program directly copies merge_sort() and merge() algorithms    
//               from mergesort.cpp and uses them to measure running times for 
//               10 different sizes of vectors.
//============================================================================

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;
auto N = 5000; // This is the size of the minimum array to be sorted.

// merging two sorted lists
void merge(vector<int>& to_sort, vector<int>& left, vector<int>& right)
{
    auto sizeL = left.size();
    auto sizeR = right.size();

    auto i = 0,j = 0,k = 0;

    // look up to first elements and choose smaller one
    while (j < sizeL && k < sizeR)
    {
        to_sort[i++] = (left[j] < right[k]) ? left[j++] : right[k++];
    }

    // in case anything left in the left part
    while (j < sizeL)
    {
        to_sort[i++] = left[j++];
    }

    // in case anything left in the right part
    while (k < sizeR)
    {
        to_sort[i++] = right[k++];
    }
}


void merge_sort(vector<int>& to_sort)
{
    // 1 or 0 elements are already sorted
    if (to_sort.size() < 2) {
        return;
    }

    // divide the array into two parts from the middle
    auto left = vector<int>();
    auto right = vector<int>();

    for (auto i = 0; i < to_sort.size() / 2; ++i)
    {
        left.push_back(to_sort[i]);
    }

    for (auto i = to_sort.size() / 2; i < to_sort.size(); ++i)
    {
        right.push_back(to_sort[i]);
    }

    // sort left, sort right & merge 
    merge_sort(left);
    merge_sort(right);
    merge(to_sort, left,right);

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

        for (auto attempts = 0; attempts < 3 ; ++attempts)  // to smooth the running time
        {
            auto to_sort = vector<int>();

            // put random integers to vector
            for (auto j = 0; j < i ; ++j)
            {
                to_sort.push_back(uni(rng));
            }
            
            auto start = chrono::steady_clock::now();
            merge_sort(to_sort);
            auto end = chrono::steady_clock::now();

            auto time = chrono::duration_cast<chrono::microseconds>(end - start).count(); // in microseconds
            total_time_elapsed += time; // just add up, average is calculated later
            
            to_sort.clear();
        }
         cout << "    " <<  i << "          " << total_time_elapsed / 1000.0f / 3.0f  << endl;
    }
}
