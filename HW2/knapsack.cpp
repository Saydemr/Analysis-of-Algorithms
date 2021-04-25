//============================================================================
// Name        : knapsack.cpp
// Author      : Abdullah Saydemir
// Version     : 1.6
// Copyright   : BSD
// Date        : March 18, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of knapsack algorithm in both recursive  
//               and dynamic programming fashion. main() creates random integers for   
//               values and weights, calls knapsack with that integer arrays, prints 
//               the time elapsed and total value of items that can be fit to knapsack 
//               
//============================================================================

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>

using namespace std;

int knapsack_recursive( const vector<int>& wt, const vector<int>& val, int W, int n)
{

    if (W == 0 || n == 0) // If there is no space in the knapsack or there are no items left
    {
        return 0;
    }
    else if ( wt[n-1] > W )  {  // If the next item is too big to put into the knapsack
        return knapsack_recursive(wt, val, W, n-1);
    }
    else { // If we can put the item to knapsack
        return max(val[n-1] + knapsack_recursive(wt, val, W - wt[n-1], n-1), // if we take the item
                              knapsack_recursive(wt, val, W, n-1));          // if we don't take the item
    }

}

int knapsack_dp( const vector<int>& wt, const vector<int>& val, int W, int n)  
{
    // initialize the table
    int table[n+1][W+1];

    // set the base cases
    for (int i = 0; i < n+1; ++i)              // If w = 0, no capacity
    {
        table[i][0] = 0;
    }

    for (int j = 0; j < W+1; ++j)              // If n = 0, no items
    {
        table[0][j] = 0;
    }

    // fill the table
    for (auto i = 1; i < n+1; ++i)
    {
        for (auto w = 1; w < W+1; ++w)
        {
            if (wt[i-1] <= w)                                          // if the item can fit into knapsack
            {
                table[i][w] = max(val[i-1] + table[i-1][w - wt[i-1]] , // if we take the item
                                                       table[i-1][w]); // if we leave the item
            }
            else {                                                     // If the item is too big to put into knapsack
                table[i][w] = table[i-1][w];
            }
        }
    }

    return table[n][W]; 
}


int main()
{
    // initialize random number generator engines
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> unival(1,100); 
    uniform_int_distribution<int> uniwt(1,15); 
    
    // capacity
    //auto W = 100;
    auto N = 30;

    // to handle random integers
    auto val = vector<int>();
    auto wt = vector<int>();

    for (auto i = 40 ; i <= 100 ; i+=10) 
    {
        
        // create random values and put them into the arrays
        for (auto j = 0; j < i ; ++j) 
        {
            val.push_back(unival(rng));
            wt.push_back(uniwt(rng));
        }

        // How long the algorithm runs ?
        auto time_rec_avg = 0.0;
        auto time_dp_avg = 0.0;

        // What is the maximum value we can get ?
        auto max_dp = 0;
        auto max_rec = 0;

        // multiple runs, to take the average
        for (int t = 0; t < 3; ++t)
        {
            
            auto start = chrono::steady_clock::now();                    // start the clock
            max_rec = knapsack_recursive(wt,val,i,N);                    // run the code (Recursive)
            auto end = chrono::steady_clock::now();                      // stop the clock
            time_rec_avg += chrono::duration_cast<chrono::nanoseconds>(end - start).count();    


            start = chrono::steady_clock::now();                        // start the clock
            max_dp = knapsack_dp(wt,val,i,N);                           // run the code (Dynamic)
            end = chrono::steady_clock::now();                          // stop the clock
            time_dp_avg += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        }

        // take the average, turn to milliseconds
        time_dp_avg = time_dp_avg *1e-6 / 3.0;
        time_rec_avg = time_rec_avg *1e-6 / 3.0;

        
        // print the data
        printf("N = %d W = %d Rec time = %4.3lf DP time = %1.4lf Rec Max = %d DP Max = %d \n", N, i, time_rec_avg, time_dp_avg, max_rec, max_dp);
        
        //clear the arrays
        val.clear();
        wt.clear();
    }

    auto W = 100;

    for (auto i = 10 ; i <= 30 ; i+=4) 
    {
        
        // create random values and put them into the arrays
        for (auto j = 0; j < i ; ++j) 
        {
            val.push_back(unival(rng));
            wt.push_back(uniwt(rng));
        }

        // How long the algorithm runs ?
        auto time_rec_avg = 0.0;
        auto time_dp_avg = 0.0;

        // What is the maximum value we can get ?
        auto max_dp = 0;
        auto max_rec = 0;

        // multiple runs, to take the average
        for (int t = 0; t < 3; ++t)
        {
            
            auto start = chrono::steady_clock::now();                    // start the clock
            max_rec = knapsack_recursive(wt,val,W,i);                    // run the code (Recursive)
            auto end = chrono::steady_clock::now();                      // stop the clock
            time_rec_avg += chrono::duration_cast<chrono::nanoseconds>(end - start).count();    


            start = chrono::steady_clock::now();                        // start the clock
            max_dp = knapsack_dp(wt,val,W,i);                           // run the code (Dynamic)
            end = chrono::steady_clock::now();                          // stop the clock
            time_dp_avg += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        }

        // take the average, turn to milliseconds
        time_dp_avg = time_dp_avg *1e-6 / 3.0;
        time_rec_avg = time_rec_avg *1e-6 / 3.0;

        
        // print the data
        printf("N = %d W = %d Rec time = %4.3lf DP time = %1.4lf Rec Max = %d DP Max = %d \n", i, W, time_rec_avg, time_dp_avg, max_rec, max_dp);
        
        //clear the arrays
        val.clear();
        wt.clear();
    }


    return 0;
}