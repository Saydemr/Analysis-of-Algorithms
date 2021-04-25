//============================================================================
// Name        : mergesort.cpp
// Author      : Abdullah Saydemir
// Version     : 1.1
// Copyright   : BSD
// Date        : March 9, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of merge sort algorithm in recursive  
//               fashion. main() reads inputs from data.txt sorts the inputs with    
//               merge_sort() and outputs it to console.
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// merging two sorted lists
void merge(vector<int>& to_sort, vector<int>& left, vector<int>& right)
{
    int sizeL = left.size();
    int sizeR = right.size();

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

void print(const vector<int>& to_print)
{
    for (auto i = 0; i < to_print.size()-1; ++i)
    {
        cout << to_print[i] << " ";
    }
    cout << to_print[to_print.size()-1] << endl;

}

int main() {

    string testfile = "data.txt";

    ifstream file(testfile.c_str());
    if (file.is_open())
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
        for (int i = 0; i < size ; ++i) {    
            cin >> newbie;
            to_sort.push_back(newbie);
        }

        // sort & print
        merge_sort(to_sort);
        print(to_sort);

    }

}
