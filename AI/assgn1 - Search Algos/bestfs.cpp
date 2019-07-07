#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>

using namespace std;

void print(vector<vector<char> > x)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << x[i][j] << " ";
		}
		cout << "\n";
	}
}

vector<vector<char> > swap(vector<vector<char> > a, int i1, int j1, int i2, int j2)
{
	char temp = a[i1][j1];
	a[i1][j1] = a[i2][j2];
	a[i2][j2] = temp;
	
	return a;
}

vector<vector<vector<char> > > get_neighbours(vector<vector<char> > config)
{
	int i, j;
	bool found = false;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (config[i][j] == ' ')
			{
				found = true;
				break;
			}
		}
		if (found)
			break;
	}

	// calculate neighbours
	vector<vector<vector<char> > > neighbours;
	
	if (i - 1 >= 0)
	{	
		vector<vector<char> > temp = config;
		neighbours.push_back(swap(temp, i, j, i - 1, j));
		
	}
	if (i + 1 <= 2)
	{
		vector<vector<char> > temp = config;
		neighbours.push_back(swap(temp, i, j, i + 1, j));
	}
	if (j - 1 >= 0)
	{
		vector<vector<char> > temp = config;
		neighbours.push_back(swap(temp, i, j, i, j - 1));
	}
	if (j + 1 <= 2)
	{
		vector<vector<char> > temp = config;
		neighbours.push_back(swap(temp, i, j, i, j + 1));
	}

	return neighbours;
}

bool find(vector<vector<vector<char> > > arr, vector<vector<char> > to_find)
{
	for (vector<vector<char> > i : arr)
	{
		if (i == to_find)
			return true;
	}

	return false;
}

int euclidean_distance(vector<vector<char> > nodes, vector<vector<char> > goal)
{
	int sum = 0;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (goal[i][j] != ' ' && goal[i][j] == nodes[k][l])
						sum += sqrt((i - k)*(i - k) + (j - l)*(j - l));
				}
			}
		}
	}
	
	return sum;
}
// something is wrong
//int out_of_row_col(vector<vector<char> > nodes, vector<vector<char> > goal)
//{
//	int sum = 0;
//	
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			if (nodes[i][j] != ' ' && nodes[i][j] != goal[i][j])
//				sum += 1;
//		}
//	}
//	
//	for (int j = 0; j < 3; j++)
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			if (nodes[i][j] != ' ' && nodes[i][j] != goal[i][j])
//				sum += 1;
//		}
//	}
//	
//	return sum;
//}

vector<pair<vector<vector<char> >, int> > get_scores(vector<vector<vector<char> > > nodes, vector<vector<char> > goal)
{
	vector<pair<vector<vector<char> >, int> > scores;
	for (auto node : nodes)
	{
		scores.push_back(make_pair(node, euclidean_distance(node, goal)));
	}
	
	return scores;
}

struct ordering {
    bool operator ()(pair<vector<vector<char> >, int> const& a, 
                     pair<vector<vector<char> >, int> const& b) {
        return a.second < b.second;
    }
};

int main(void)
{
	vector<vector<char> > initial_config = { {'8', '4', '7'},
												{'1', '6','5'},
												{'2', '3', ' '}
											};
	vector<vector<char> > goal = { {'1', '8', '7'},
									{'2', ' ', '6'},
									{'3', '4', '5'}
								};

	deque<vector<vector<vector<char> > > > queue;
	vector<vector<vector<char> > > visited;
	queue.push_back({ initial_config });

	while (queue.size() != 0)
	{
		vector<vector<vector<char> > > path = queue.front();
		queue.pop_front();

		vector<vector<char> > last = path[path.size() - 1];

		// if the neighbour is the goal
		if (last == goal)
		{
			cout << "Path to goal:\n";
			for (vector<vector<char> > x : path)
			{
				print(x);
				cout << "\n";
			}
			return 0;
		}

		// get neighbours
		vector<vector<vector<char> > > neighbours = get_neighbours(last);
		
		// sort neighbours
		vector<pair<vector<vector<char> >, int> > scores = get_scores(neighbours, goal);
		sort(scores.begin(), scores.end(), ordering());

		vector<vector<vector<char> > > sorted_neighbours;
		for (int i = 0; i < scores.size(); i++)
		{
			sorted_neighbours.push_back(scores[i].first);
		}
	
		for (int c = 0; c < sorted_neighbours.size(); c++)
		{
			// extend that neighbour
			if (!find(visited, sorted_neighbours[c]))
			{
				vector<vector<vector<char> > > temp = path;
				temp.push_back(sorted_neighbours[c]);
				queue.push_back(temp);
				visited.push_back(sorted_neighbours[c]);
			}
		}
	}

	cout << "Could not find goal\n";

	return 0;
}
