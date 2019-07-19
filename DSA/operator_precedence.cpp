#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>

using namespace std;

void preprocessor(string& str)
{
	for (basic_string<char>::iterator i = str.begin(); i != str.end(); i++)
		if (*i == '(')
			i = str.insert(i + 1, ' ') + 1;
		else if (*i == ')')
			i = str.insert(i, ' ') + 1;
}

pair<int, int> operate(char opCode, pair<int, int>& val2, pair<int, int>& val1, vector<pair<char, int> >& curr_vals, vector<char>& changed)
{
	if (opCode == '=')
	{
		if (!(val2.first == 1)) // opr2(LHS) should be a valid variable
		{
			throw runtime_error("LHS of assignment should be a valid variable.");
		}

		if (val1.first == 1) // opr1 should be an enumerable value
		{
			bool assigned = false;
			for (auto i : curr_vals)
				if (i.first == val1.second)
				{
					val1.first = 0;
					val1.second = i.second;
					assigned = true;
					break;
				}
			if (!assigned) // RHS is undefined
				throw runtime_error("RHS is undefined.");
		}

		// now assign value to variable
		bool assigned = false;
		for (auto& i : curr_vals)
			if (i.first == val2.second)
			{
				i.second = val1.second;
				assigned = true;
				break;
			}

		pair<char, int> temp(val2.second, val1.second);
		if (!assigned) curr_vals.push_back(temp);

		changed.push_back(val2.second);
	}
	else if (opCode == '+' || opCode == '-' || opCode == '*' || opCode == '/')
	{
		// convert variables to values
		if (val1.first == 1) // should be a valid value
		{
			for (auto i : curr_vals)
				if (i.first == val1.second)
				{
					val1.first = 0;
					val1.second = i.second;
				}
		}
		if (val2.first == 1) // should be a valid value
		{
			for (auto i : curr_vals)
				if (i.first == val2.second)
				{
					val2.first = 0;
					val2.second = i.second;
				}
		}

		// check if both are valid, or were converted to values successfully
		if (val1.first == 1 || val2.first == 1)
		{
			string err = "Both LHS and RHS of "; err += opCode; err += " operation should be a defined variable or value.";
			throw runtime_error(err);
		}

		// perform the appropriat operation
		if (opCode == '+')
			val1.second += val2.second;
		else if (opCode == '-')
			val1.second -= val2.second;
		else if (opCode == '*')
			val1.second *= val2.second;
		else if (opCode == '/')
			val1.second = val2.second / val1.second;
	}

	return val1;
}

int main(void)
{
	ifstream in_file("input.txt");

	if (!in_file)
	{
		cout << "File does not exist!\n";
		return 0;
	}

	// using 2 stacks
	stack<pair<int, int>> invalidators; // 1st int is 1, if it is a variable
	stack<char> operators;

	vector<pair<char, int>> curr_vals;

	int line_counter = 0;

	while (!in_file.eof())
	{
	new_line:
		string line;
		getline(in_file, line);
		preprocessor(line);

		if (in_file.eof())
			break;

		// for debugging
		line_counter++;

		vector<char> changed; // values which changed in current line

		istringstream tokenizer(line);

		// tokenize current line
		string token;
		while (tokenizer >> token)
		{
			if (token == "#") // EOF
			{
				goto new_line;
			}

			pair<int, int> temp;

			if (token[0] == '(')
				operators.push(token[0]);
			else if (token[0] == ')')
			{
				char opCode;

				pair<int, int> opr1;
				pair<int, int> opr2;

				while (operators.top() != '(')
				{
					// get next
					opCode = operators.top();
					operators.pop();

					opr1 = invalidators.top();
					invalidators.pop();
					opr2 = invalidators.top();
					invalidators.pop();

					pair<int, int> temp = operate(opCode, opr2, opr1, curr_vals, changed);
					invalidators.push(temp);
				}
				operators.pop();
			}
			else if (token[0] == '~' || token[0] >= '0' && token[0] <= '9')
			{
				temp.first = 0;
				if (token[0] == '~')
				{
					token[0] = '0';
					temp.second = stoi(token);
					temp.second *= -1;
				}
				else
					temp.second = stoi(token);

				invalidators.push(temp);
			}
			else if (token[0] >= 'A' && token[0] <= 'Z')
			{
				temp.first = 1;
				temp.second = token[0];
				invalidators.push(temp);
			}
			else
			{
				char opCode = token[0];
				char opOnTop;

				if (operators.empty())
				{
					operators.push(opCode);
					continue;
				}

				// precedence
				opOnTop = operators.top();
				if ((opCode == '+' || opCode == '-') && (opOnTop == '*' || opOnTop == '/'))
				{
					// stack swap
					operators.pop();

					pair<int, int> temp1 = invalidators.top(); invalidators.pop();
					pair<int, int> temp2 = invalidators.top(); invalidators.pop();

					tokenizer >> token; // next value

					// push next value
					if (token[0] == '~' || token[0] >= '0' && token[0] <= '9')
					{
						temp.first = 0;
						if (token[0] == '~')
						{
							token[0] = '0';
							temp.second = stoi(token);
							temp.second *= -1;
						}
						else
							temp.second = stoi(token);
					}
					else if (token[0] >= 'A' && token[0] <= 'Z')
					{
						temp.first = 1;
						temp.second = token[0];
					}

					invalidators.push(temp);

					// push temp1 and temp2
					invalidators.push(temp2);
					invalidators.push(temp1);

					// swap opOnTop and opCode
					operators.push(opCode);

					opCode = opOnTop;
				}

				operators.push(opCode);
			}
		}

		// for each operator, pop two invalidators and push one enumerable value to invalidators
		while (!operators.empty())
		{
			char opCode = operators.top();
			operators.pop();

			pair<int, int> opr1 = invalidators.top();
			invalidators.pop();
			pair<int, int> opr2 = invalidators.top();
			invalidators.pop();

			pair<int, int> result = operate(opCode, opr2, opr1, curr_vals, changed);
			invalidators.push(result);
		}

		// print value of each variable in the line
		if (changed.empty())
			cout << "No change\n";
		for (auto j : changed)
			for (auto i : curr_vals)
				if (i.first == j)
					cout << i.first << " = " << i.second << ", ";
		cout << '\n';
	}

	in_file.close();

	return 0;
}
