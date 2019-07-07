#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(void)
{
	ifstream infile("input1.txt");

	string find;
	getline(infile, find);
	int line_counter = 0;

	while (true)
	{
		string line;
		string word;

		if (infile.eof())
			break;

		getline(infile, line);
		line_counter++;
		
		istringstream input_line(line);
		int word_counter = 0;

		while (input_line >> word)
		{
			if (word == find)
			{
				word_counter++;
			}
		}

		cout << "Line number: " << line_counter << " Words found: " << word_counter << endl;
	}

	infile.close();

	system("PAUSE");
	return 0;
}
