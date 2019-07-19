#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void give_me_what_i_want(string raw_line, string& roll_num, string& choices) // & means by reference
{
	int iterator = 0;
	while (raw_line[iterator] != ' ')
	{
		roll_num += raw_line[iterator]; // concatenation
		iterator++;
	}

	iterator++; // skip the blank space

	while (raw_line[iterator] != '\0') // \0 or NULL is the end of line
	{
		choices += raw_line[iterator];
		iterator++;
	}
}

int main(void)
{
	ifstream in_file("Exam.txt");
	ofstream out_file("output_Exam.txt");

	string solution;
	getline(in_file, solution);

	while (true)
	{
		string roll_num = "", choices = "";
		string raw_line;

		getline(in_file, raw_line);

		give_me_what_i_want(raw_line, roll_num, choices);
		//cout << roll_num << ' ' << choices << endl;

		// process
		int correct_answers = 0, wrong_answers = 0; // missed answers = total_questions - (correct_answers + wrong_answers)
		int final_score;
		for (int i = 0; i < solution.length(); i++)
		{
			if (choices[i] == solution[i])
			{
				correct_answers++;
			}
			else
			{
				wrong_answers++;
			}
		}

		final_score = correct_answers * 2 - wrong_answers;

		// write output - START
		out_file << roll_num << ' ' << correct_answers << ' ' << wrong_answers << ' ' << solution.length() - (correct_answers + wrong_answers) << ' ';
		out_file << final_score << ' ';

		double percentage = double(final_score) / solution.length();
		cout << percentage << endl;

		if (percentage >= 0.9)
		{
			out_file << 'A';
		}
		else if (percentage >= 0.8)
		{
			out_file << 'B';
		}
		else if (percentage >= 0.7)
		{
			out_file << 'C';
		}
		else if (percentage >= 0.6)
		{
			out_file << 'D';
		}
		else
		{
			out_file << 'F';
		}

		out_file << '\n'; // next line
		// write output - END

		if (in_file.eof())
			break;
	}

	in_file.close();
	out_file.close();

	system("PAUSE");

	return 0;
}
