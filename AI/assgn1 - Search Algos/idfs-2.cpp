#include <iostream>
#include <vector>
#include <stack>

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

	int depth = 1;

	// DFS
	while (depth <= 20)
	{
		cout << "Looking at depth: " << depth << endl;

		stack<vector<vector<vector<char> > > > stack;
		vector<vector<vector<char> > > visited;
		stack.push({ initial_config });

		while (!stack.empty())
		{
			vector<vector<vector<char> > > path = stack.top();
			stack.pop();

			// get neighbours
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

			// depth bound
			if (path.size() >= depth)
				continue;

			vector<vector<vector<char> > > neighbours = get_neighbours(last);
		
			for (int c = 0; c < neighbours.size(); c++)
			{
				// extend that neighbour
				if (!find(visited, neighbours[c]))
				{
					vector<vector<vector<char> > > temp = path;
					temp.push_back(neighbours[c]);
					stack.push(temp);
					visited.push_back(neighbours[c]);
				}
			}
		}

		depth++;
	}

	cout << "Could not find goal\n";

	return 0;
}
