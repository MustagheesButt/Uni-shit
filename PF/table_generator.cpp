#include <iostream>

using namespace std;

int main()
{
	
	int size ,table;
	cout << "Enter the size of table" << '\n';
	cin >> size;
	
	for (int i = 1; i <= size; i++)
	{
		cout << '\t' << i;
	}
	cout << '\n';
	cout << "_____________________________________________________________________________________________________________" << '\n';
	
	for (int i = 1; i <= size; i++)
	{
	    cout << '\t' << i << "|";
		for (int j = 1; j <= size; j++)
		{
			table = i * j;
			cout << table << '\t';
		}
		cout << '\n';
	}
	
	return 0;
}

