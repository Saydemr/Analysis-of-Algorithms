#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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


vector<Activity> last_to_start(vector<Activity>& sorted_activities) 
{
	auto n = sorted_activities.size();

	auto v = vector<Activity>{};
	v.push_back(sorted_activities.back());

	auto i = n-1;

	for (int m = n-2; m > -1 ; --m)
	{
		if (sorted_activities[m].finish <= sorted_activities[i].start )
		{
			v.push_back(sorted_activities[m]);
			i = m;
		}
	}

	return v;
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

    int test_size = 0;
    while (cin >> test_size)
    {
        auto all_activities = vector<Activity>{};

        int start;
        int finish;
        int id;

        for (auto i = 0; i < test_size; ++i)
        {
            cin >> id;
            cin >> start;
            cin >> finish;

            all_activities.push_back(Activity(id,start,finish));
        }

        merge_sort(all_activities);
        // sort(activities.begin(), activities.end(), [&](Activity fst, Activity sec) {return fst.start < sec.start;} ); I would love to use this line

        auto selected = last_to_start(all_activities);
        auto size = selected.size();

        cout << "Set " << count << endl;
        cout << "Maximum number of activities = " << size << endl;
        for (int i = size-1; i > -1; --i)
        {
        	cout << selected[i].id << " ";
        }
        cout << endl;

        count++;
        selected.clear();
        all_activities.clear();
    }
}
