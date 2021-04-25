//============================================================================
// Name        : mergesort.cpp
// Author      : Abdullah Saydemir
// Version     : 1.1
// Copyright   : BSD
// Date        : March 9, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of insertion sort algorithm in recursive  
//               fashion. main() reads inputs from data.txt, sorts the inputs with    
//               insertion_sort() and outputs it to console.
//
//				 Very similar Insertion Sort algorithm code is available on my GitHub
//				 repo from one of my previous classes. (CS201 - Ozyegin University)
//				
//				 https://github.com/Saydemr/DataStructures-Algorithms/blob/master/SelectionAlgorithm.cpp
//				
//				 SelectionAlgorithm::insertionSort()
//============================================================================


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void insertion_sort(vector<int>& to_sort)
{
    for (auto i = 1; i < to_sort.size(); ++i) // start from the first index
    {
        auto pivot = to_sort[i]; // current element to insert
        auto j = i; // pointer

        while ((j > 0) && (to_sort[j-1] > pivot)) // go left on the array while pivot is less than previous element
        {
            to_sort[j] = to_sort[j - 1]; // shift elements to right
            j = j - 1;

        }
        to_sort[j] = pivot; // put pivot to correct place
    }
}

// Traverse the array and print all elements.
void print(const vector<int>& to_print)
{
    for (auto i = 0; i < to_print.size()-1; ++i)
    {
        cout << to_print[i] << " ";
    }
    cout << to_print[to_print.size()-1] << endl;
}

int main() {

    string testfile = "data.txt"; // Test file is always "data.txt". No need for argv

    ifstream file(testfile.c_str());
    
    if (file.is_open())  // Check if the file is correctly opened.
    {
        cin.rdbuf(file.rdbuf());
    }
    else {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    auto size = 0;

    // Do this until there is no integer left to read. This line also gets the first item in each line which is size.
    while (cin >> size)
    {
        auto to_sort = vector<int>(); // vector to sort
        auto newbie = 0; // to store the new item
        
        // put the line to a vector
        for (auto i = 0; i < size ; ++i) {
            cin >> newbie;
            to_sort.push_back(newbie);
        }

        // sort and print
        insertion_sort(to_sort);
        print(to_sort);

    }

}
