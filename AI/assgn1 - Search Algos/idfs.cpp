#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Instance {
	vector<char> arr;

public:
	Instance(char arr[])
	{
		for (int i = 0; i < 9; i++)
		{
			this->arr.push_back(arr[i]);
		}
	}

	char get(int i, int j)
	{
		return this->arr[i * 3 + j];
	}

	void set(int i, int j, char val)
	{
		this->arr[i * 3 + j] = val;
	}

	void swap(Instance* a, int i1, int j1, int i2, int j2)
	{
		char temp = a->get(i1, j1);
		a->set(i1, j1, a->get(i2, j2));
		a->set(i2, j2, temp);
	}

	void print()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << this->get(i, j) << " ";
			}
			cout << "\n";
		}
	}

	vector<Instance> get_neighbours(Instance obj)
	{
		int i, j;
		bool found = false;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (obj.get(i, j) == ' ')
				{
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		//i--; j--;

		// calculate neighbours
		vector<Instance> neighbours;
		
		if (i - 1 >= 0)
		{
			Instance temp1(obj);
			this->swap(&temp1, i, j, i - 1, j);
			neighbours.push_back(temp1);
		}
		if (i + 1 <= 2)
		{
			Instance temp1(obj);
			this->swap(&temp1, i, j, i + 1, j);
			neighbours.push_back(temp1);
		}
		if (j - 1 >= 0)
		{
			Instance temp1(obj);
			this->swap(&temp1, i, j, i, j - 1);
			neighbours.push_back(temp1);
		}
		if (j + 1 <= 2)
		{
			Instance temp1(obj);
			this->swap(&temp1, i, j, i, j + 1);
			neighbours.push_back(temp1);
		}

		return neighbours;
	}

	bool operator==(Instance& obj)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->get(i, j) != obj.get(i, j))
					return false;
			}
		}

		return true;
	}
};

bool find(vector<Instance> arr, Instance to_find)
{
	for (Instance i : arr)
	{
		if (i == to_find)
			return true;
	}

	return false;
}

int main(void)
{
	char initial_config[9] = {'1', '8', '2', ' ', '4','3', '7', '6', '5'};
	char goal[9] = { '1', '2', '3', '4', ' ', '5', '6', '7', '8' };

	Instance ic(initial_config);
	Instance g(goal);

	int depth = 1;

	// da real DFS
	while (depth <= 20)
	{
		cout << "Finding at depth: " << depth << endl;

		stack<vector<Instance>> stack;
		vector<Instance> visited;
		stack.push({ ic });

		while (!stack.empty())
		{
			vector<Instance> path = stack.top();
			stack.pop();

			// get neighbours
			Instance last = path[path.size() - 1];

			// if the neighbour is the goal
			if (last == g)
			{
				cout << "Path to goal:\n";
				for (Instance x : path)
				{
					x.print();
					cout << "\n";
				}
				return 0;
			}

			// depth bound
			if (path.size() >= depth)
				continue;

			vector<Instance> neighbours = last.get_neighbours(last);
			
			for (int c = 0; c < neighbours.size(); c++)
			{
				// extend that neighbour
				if (!find(visited, neighbours[c]))
				{
					vector<Instance> temp = path;
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