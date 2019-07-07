#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdbool.h>

#include <windows.h>

using namespace std;

#include "core.h"
#include "helpers.h"

void gotoxy(int x, int y) // retarded method
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

void clear_line()
{
	for (int i = 0; i < 85; i++)
		cout << " ";
}

int write_matrix(ofstream &file, char matrix[][SIZE])
{
	int arr_size = SIZE * SIZE;
	for (int i = 0; i < arr_size; i++)
	{
		if (matrix[0][i] == '\0')
		{
			file << "- ";
			continue;
		}
		file << matrix[0][i] << ' ';
	}
	return 0;
}

string temp_save(Player players_array[], int turn, char array[][SIZE])
{
	ofstream file(F_SAVE);

	if (file.is_open())
	{
		// store player info
		for (int i = 0; i < 2; i++)
			file << players_array[i].name << ' ' << players_array[i].id << endl;

		// store turn
		file << turn << endl;

		// store matrix
		write_matrix(file, array);

		file.close();

		return "Current data saved temporarily!\n";
	}
	return "Failed to open the save data file\n";
}

string temp_clear()
{
	fstream file(F_SAVE, ios::out | ios::trunc);
	if (file.is_open())
	{
		file.close();
		return "Temporary save data file cleared!\n";
	}
	file.close();
	return "Failed to open the save data file.\n";
}

bool temp_is_empty(string file)
{
	/*
	* Taken from: https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
	*/
	ifstream file_ptr(file);
	bool result = file_ptr.peek() == ifstream::traits_type::eof();
	file_ptr.close();
	return result;
}

string temp_load(Player players[], int* turn, char game_matrix[][SIZE])
{
	ifstream file(F_SAVE);
	if (file.is_open())
	{
		// player 1 data
		file >> players[0].name;
		file >> players[0].id;

		// player 2 data
		file >> players[1].name;
		file >> players[1].id;

		// turn
		file >> *turn;
		*turn = *turn + 1; // next player's turn

		// game matrix data
		for (int i = 0; i < SIZE * SIZE; i++)
		{
			char temp;
			file >> temp;
			if (temp == '-')
				game_matrix[0][i] = '\0';
			else
				game_matrix[0][i] = temp;
		}
		file.close();
		return "Temporary save data file read successfully!\n";
	}
	file.close();
	return "Failed to open the save data file.\n";
}

int declare_result(int result, string name)
{
	system("CLS");
	if (result == 0)
	{
		PlaySound(TEXT("res/sfx1.dll"), NULL, SND_ASYNC);
		cout << name << " won the match\n";
	}
	else
	{
		PlaySound(TEXT("res/sfx2.dll"), NULL, SND_ASYNC);
		cout << "The match is a DRAW!!!\n";
	}
	cout << "Thank you for playing the game!\n";
	return 0;
}

int save_history(int result, Player players[], char game_matrix[][SIZE])
{
	ofstream file("HIST.dat", ios::app);
	if (!file.is_open())
	{
		cout << "HIST.dat could not be opened!\n";
		return -1;
	}
	file << result << ' ';
	file << players[0].name << ' ' << (players[0].id == 0 ? 'X' : 'O') << ' ';
	file << players[1].name << ' ' << (players[1].id == 0 ? 'X' : 'O') << ' ';
	write_matrix(file, game_matrix);
	file << endl;
	file.close();
	return 0;
}

int show_history()
{
	int winner;
	string p1, sym1, p2, sym2;
	char matrix[SIZE][SIZE];

	ifstream file("HIST.dat");
	if (!file.is_open())
	{
		cout << "File could not be opened! It probably does not exist. Make sure you have at least played once before trying to see history.\n";
		return -1;
	}
	// read all records
	int counter = 0;
	system("CLS");
	while (counter <= 9)
	{
		file >> winner >> p1 >> sym1 >> p2 >> sym2;
		if (!file)
			break;
		if (winner == 0)
			cout << (counter + 1) << ". " << p1 << " WINNER!\n";
		else if (winner == 1)
			cout << (counter + 1) << ". " << p2 << " WINNER!\n";
		else
			cout << (counter + 1) << ". DRAW!\n";
		cout << p1 << " (" << sym1 << ") VS " << p2 << " (" << sym2 << ")\n";

		int arr_size = SIZE * SIZE;
		for (int i = 0; i < arr_size; i++)
		{
			char temp;
			file >> temp;
			if (temp == '-')
				matrix[0][i] = '\0';
			else
				matrix[0][i] = temp;
		}
		show_table(matrix);
		counter++;
	}
	file.close();
	return 0;
}
