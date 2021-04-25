//============================================================================
// Name        : shopping.cpp
// Author      : Abdullah Saydemir
// Version     : 1.2
// Copyright   : BSD
// Date        : March 20, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes very similar dp implementation of knapsack algorithm in  
//               knapsack.cpp. Difference is that this algorithm returns the items.   
//               main() reads input from shopping.txt solves the "Shopping Spree" 
//               problem described in the homework with the help of knapsack algorithm.
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// knapsack algorithm returning the list of items rather than the max value
vector<int> knapsack_dp( const vector<int>& wt, const vector<int>& val, int W, int n)
{

      // initialize the table
    int table[n+1][W+1];

    // set the base cases
    for (int i = 0; i < n+1; ++i) // If w = 0, no capacity
    {
        table[i][0] = 0;
    }

    for (int j = 0; j < W+1; ++j) // If n = 0, no items
    {
        table[0][j] = 0;
    }

    // fill the table
    for (auto i = 1; i < n+1; ++i)
    {
        for (auto w = 1; w < W+1; ++w)
        {
            if (wt[i-1] <= w) // if the item can fit into knapsack
            {
                table[i][w] = max(val[i-1] + table[i-1][w - wt[i-1]] , // if we take the item
                                                       table[i-1][w]); // if we leave the item
            }
            else { // If the item is too big to put into knapsack
                table[i][w] = table[i-1][w];
            }
        }
    }


    auto i = n;
    auto j = W;

    auto item_ids = vector<int>();


    while ( i > 0 && j > 0)                            // start from end, go backwards
    {
        if (table[i][j] != table[i-1][j])              // weight difference, item is in the knapsack
        {
            item_ids.insert(item_ids.begin(),i-1);     // put the item to the return list
            j = j - wt[i-1];                           // reduce the weight
        }
        --i;
    }

    return item_ids;
}




int main()
{
    string testfile = "shopping.txt";                       // Test file is always "shopping.txt". No need for argv

    ifstream file(testfile.c_str());
    
    if (file.is_open())                                     // Check if the file is correctly opened.
    {
        cin.rdbuf(file.rdbuf());
    }
    else {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    // number of tests
    auto T = 0;
    cin >> T;

    
    //number of items
    auto N = 0;

    for (auto i = 0; i < T ; ++i) 
    {

        cin >> N;

        auto wt = vector<int>();                  // weights
        auto val = vector<int>();                 // values

        auto price = 0;
        auto weight = 0;

        // read the weights and values of items
        for (auto j = 0; j < N; ++j)
        {
            cin >> price;
            cin >> weight;
            val.push_back(price);
            wt.push_back(weight);
        }
        
        // number of family members
        auto F = 0;
        cin >> F;

        auto carry = 0;
        auto total_price = 0;
        

        auto family_items = vector< vector<int> >();             // which items each family member carry
        auto var = vector<int>();

        
        for (int k = 0; k < F; ++k)
        {
            cin >> carry;                                        // get how much the current member can carry

            var = knapsack_dp(wt, val, carry, N);               // run knapsack and get the items

            for (auto p = 0;  p < var.size() ; ++p) 
            {

                total_price += val[var[p]];                     // add values to the total price

            }
            family_items.push_back(var);                        // put it to item list to print later 

        }

        // PRINT ALL THE INFO
        cout << "Test Case " << i+1 << endl;
        cout << "Total Price " << total_price << endl;

        // print the members and the items
        for (auto q = 0; q < family_items.size(); ++q)
        {
            cout << (q+1) << ": ";                                // member number
            for (auto s = 0; s < family_items[q].size(); ++s)
            {
                cout << family_items[q][s] + 1 << " ";            // items he/she carries

            }
            cout << endl;
        }

        // clear the arrays
        family_items.clear();
        wt.clear();
        val.clear();
        var.clear();

    }
    
    return 0;
}
