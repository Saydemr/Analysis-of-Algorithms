#include <iostream>
#include <vector>

using namespace std;

// 80,120, 190, 210, 330, 340, 370, 570, 890
// 200 
vector<int> roadtrip( const vector<int>& distances, int distance_limit) 
{
	auto v = vector<int>();
	int current_position = 0;
	int index = 0;

	while (current_position != distances.back()) 
	{
		int max = current_position + distance_limit;

		if ( max < distances[index+1] ) 
		{
			return vector<int>();
		}
		else {

			while (distances[index] <= max && current_position != distances.back() ) 
			{
				current_position = distances[index];
				index++; 
				//cout << current_position << "     "; 
			}
			v.push_back(--index);


		}

		for ( auto i = 0; i < v.size(); ++i) 
		{
			cout << v[i] << "  ";
		}
		cout << endl;
	}
	return v;
}





int main() {
	auto distances = vector<int>{80,120, 190, 210, 330, 340, 370, 570, 890};

	auto distance_limit = 200;

	auto v = roadtrip(distances, distance_limit);

	for ( auto i = 0; i < v.size(); ++i) 
	{
		cout << v[i] << endl;
	}

}