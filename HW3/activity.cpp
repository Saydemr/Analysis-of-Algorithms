//============================================================================
// Name        : activity.cpp
// Author      : Abdullah Saydemir
// Version     : 1.4
// Copyright   : BSD
// Date        : May 6, 2021
// Course      : CS 325 - Analysis of Algorithms
// Description : Includes the implementation of last-to-start greedy activity 
//				 selection algorithm. Uses an Activity struct to store activities.   
//               Merge sort algorithm is taken from HW1 - mergesort.cpp with only
//               is line 48. Main reads activities from act.txt, sorts them using 
//               mergesort, and sends the sorted list to last_to_start function.
//               This function greedily selects activities and returns to main.
//				 Main prints result and the selected activities for each test case.
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// this is the struct to hold activity info in one place
struct Activity
{
    int id = 0;
    int start = 0;
    int finish = 0;

    Activity() {}

    Activity(int id, int start, int finish) : id(id), start(start), finish(finish) {}

    ~Activity(){}

};

void merge(vector<Activity>& to_sort, vector<Activity>& left, vector<Activity>& right)
{
    auto sizeL = left.size();
    auto sizeR = right.size();

    auto i = 0,j = 0,k = 0;

    // look up to first elements and choose smaller one
    while (j < sizeL && k < sizeR)
    {
        to_sort[i++] = (left[j].start < right[k].start) ? left[j++] : right[k++];
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


void merge_sort(vector<Activity>& to_sort)
{
    // 1 or 0 elements are already sorted
    if (to_sort.size() < 2) {
        return;
    }

    // divide the array into two parts from the middle
    auto left = vector<Activity>();
    auto right = vector<Activity>();

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
    merge(to_sort, left, right);

}


// activity selection greedy algorithm
auto last_to_start(vector<Activity>& sorted_activities) -> vector<Activity> 
{

	auto n = sorted_activities.size();

	// create a vector to save selected activities
	auto selected = vector<Activity>{};
	// last element is always in the list
	v.push_back(sorted_activities.back());

	// pointer to last activity selected
	auto i = n-1;

	// reverse traverse the sorted activities
	for (int m = n-2; m > -1 ; --m)
	{
		// check if there is a conflict between the start time of the
		// last activity selected and the finish time of the 
		// activity we are considering to select.
		if (sorted_activities[m].finish <= sorted_activities[i].start )
		{
			// if there is no conflict take it
			// and update the pointer
			selected.push_back(sorted_activities[m]);
			i = m;
		}
	}

	return selected;
}



int main()
{
	auto count = 1;
    string testfile = "act.txt";                       // Test file is always "act.txt". No need for argv

    ifstream file(testfile.c_str());

    if (file.is_open())                                     // Check if the file is correctly opened.
    {
        cin.rdbuf(file.rdbuf());
    }
    else {
        cout << "Error: cannot read the test file!" << endl;
        return -1;
    }

    auto test_size = 0;
    while (cin >> test_size)                                              // do it until there is no more tests
    {
        auto all_activities = vector<Activity>{};

        auto start = 0;
        auto finish = 0;
        auto id = 0;

        for (auto i = 0; i < test_size; ++i)                             // take the activity id, start and finish times
        {
            cin >> id;
            cin >> start;
            cin >> finish;

            all_activities.push_back(Activity(id,start,finish));        // insert it tot activity list
        }

        merge_sort(all_activities);                                    // sort activities based on the start time
        // sort(activities.begin(), activities.end(), [&](Activity fst, Activity sec) {return fst.start < sec.start;} ); I would love to use this line

        auto selected = last_to_start(all_activities);
        auto size = selected.size();

        // PRINT
        cout << "Set " << count << endl;
        cout << "Maximum number of activities = " << size << endl;
        for (int i = size-1; i > -1; --i)
        {
        	cout << " " << selected[i].id;
        }
        cout << endl << endl;

        count++;

        // clear the variables
        selected.clear();
        all_activities.clear();
    }
}
