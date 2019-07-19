#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

void compressFile(fstream& in, fstream& out)
{
	string val;

	while (true)
	{
		getline(in, val);

		if (in.eof())
			break;

		//cout << val << endl;

		int i = 0;

		while (true)
		{
			int count_1 = 0, count_0 = 0;

			while (val[i] == '1')
			{
				count_1++;
				i++;
			}

			out << count_1;
			if (val[i] != '\0')
				out << ", ";
			else
				break;

			while (val[i] == '0')
			{
				count_0++;
				i++;
			}

			out << count_0;
			if (val[i] != '\0')
				out << ", ";
			else
				break;
		}
		out << '\n';
	}
}

void regenerateFile(fstream& in, fstream& out)
{
	string line;
	char printable_chars[] = { '1', '0' };

	in.clear();
	in.seekg(0);

	while (true)
	{
		int counter = 0;
		getline(in, line);

		if (in.eof())
			break;

		istringstream my_line(line);
		
		string token;
		
		while (getline(my_line, token, ','))
		{
			int n = stoi(token);

			for (int i = 0; i < n; i++)
			{
				out << printable_chars[counter];
			}
			counter = (counter + 1) % 2;
		}
		out << endl;
	}
}

int main()
{
	fstream in("binary.txt", ios::in);
	fstream out("compressed.txt", ios::in | ios::out);
	fstream out2("decompressed.txt", ios::out);

	compressFile(in, out);

	regenerateFile(out, out2);

	in.close();
	out.close();
	out2.close();

	system("PAUSE");

	return 0;
}
