#include <iostream>
#include <string>
#include <stdbool.h>

using namespace std;

#include "core.h"
#include "helpers.h"

int initialize(Player players_array[])
{
	char choice;
	do
	{
		cout << "\nHOW TO PLAY\n\t1. Enter 1, to see match history (if any).\n\t"
			<< "2. Press any other key to start game!\n";
		cin >> choice;
		if (choice == '1')
			show_history();
	} while (choice == '1');

	system("CLS");
	cout << "Enter player 1 name (no spaces): ";
	cin >> players_array[0].name;
	cout << "Enter player 2 name (no spaces): ";
	cin >> players_array[1].name;
	cout << players_array[0].name << " would you like X (enter 0) or O (enter 1): \n";
	cin >> players_array[0].id;
	// set player 2 identifier
	players_array[0].id == 1 ? players_array[1].id = 0 : players_array[1].id = 1;

	return 0;
}

int game_engine(Player players_array[], int init_turn, char game_matrix[][SIZE])
{
	bool hasWin;
	int resolver[SIZE * SIZE][2] = {
		{ 8, 1 },{ 12, 1 },{ 16, 1 },
		{ 8, 3 },{ 12, 3 },{ 16, 3 },
		{ 8, 5 },{ 12, 5 },{ 16, 5 }
	};

	system("CLS");
	show_table(game_matrix);
	for (int turn = init_turn; turn < 9; turn++)
	{
		int cell = ask_choice(players_array[turn % 2], game_matrix);
		//system("CLS");
		// show_table(game_matrix); // legacy
		gotoxy(resolver[cell - 1][0], resolver[cell - 1][1]);
		players_array[turn % 2].id == 0 ? cout << 'X' : cout << 'O';

		hasWin = check(game_matrix, 0, 0, 0, 1) // First horizontal line
			|| check(game_matrix, 1, 0, 0, 1) // Second horizontal line
			|| check(game_matrix, 2, 0, 0, 1) // Third horizontal line
			|| check(game_matrix, 0, 0, 1, 0) // First vertical line
			|| check(game_matrix, 0, 1, 1, 0) // Second vertical line
			|| check(game_matrix, 0, 2, 1, 0) // Third vertical line
			|| check(game_matrix, 0, 0, 1, 1) // First diagonal
			|| check(game_matrix, 0, 2, 1, -1); // Second diagonal
		if (hasWin && turn % 2 == 0)
			return 0;
		else if (hasWin && turn % 2 == 1)
			return 1;

		// temporarily save game
		temp_save(players_array, turn, game_matrix);
	}
	return -1; // draw game (tie)
}

void show_table(char array[][SIZE]) {
	int counter = 1;
	cout << "\n\t";
	for (int x = 0; x < SIZE; x++)
	{
		if (x != 0) cout << "\t_________\n\t";
		for (int y = 0; y < SIZE; y++)
		{
			if (array[x][y] != '\0')
				cout << array[x][y];
			else
				cout << counter;
			if (y != SIZE - 1) cout << " | ";
			counter++;
		}
		cout << '\n';
	}
	cout << '\n';
}
int ask_choice(Player player, char game_matrix[][SIZE]) {
	//ask user where he wants to put his tic/toe
	int cell;
	do
	{
		gotoxy(0, 10);
		clear_line();
		gotoxy(0, 10);
		cout << player.name << " enter cell number (you cannot enter the same one again): ";
		cin >> cell;
	} while (game_matrix[0][cell - 1] != '\0');
	player.id == 0 ? game_matrix[0][cell - 1] = 'X' : game_matrix[0][cell - 1] = 'O';
	return cell;
}

bool check(char b[SIZE][SIZE], int row, int col, int dr, int dc) {
	if (b[row][col] != '\0')
		return b[row][col] == b[row + dr][col + dc]
		&& b[row][col] == b[row + 2 * dr][col + 2 * dc];
	return false;
}