#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <stack>

using namespace std;

char get_pair(char x)
{
	switch (x)
	{
	case ')':
		return '(';
	case ']':
		return '[';
	default:
		break;
	}

	return NULL;
}

bool validate_expr(string expression)
{
	char map[256] = { 0 };
	map['('] = '1'; map[')'] = '(';
	map['['] = '1'; map[']'] = '[';
	map['{'] = '1'; map['}'] = '{';

	stack<char> fkin_stack;
	
	for (char ch : expression)
	{
		if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
			if (map[ch] == '1')
				fkin_stack.push(ch);
			else if (fkin_stack.empty())
				return false;
			else if (map[ch] != 0 && fkin_stack.top() != map[ch])
				return false;
			else
				fkin_stack.pop();
	}

	if (fkin_stack.empty())
		return true;
	else
		return false;
}

int main(void)
{
	int count;
	string line;
	
	ifstream infile("input-1.txt");
	
	if (infile.is_open())
	{
		// read size
		getline(infile, line);
		count = stoi(line);
		

		for (int i = 0; i < count; i++)
		{
			getline(infile, line);
			if (validate_expr(line))
				cout << "Validated!\n";
			else
				cout << "Is invalid!\n";
		}
		
		infile.close();
	}

	return 0;
}
