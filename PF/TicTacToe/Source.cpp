#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdbool.h>

#include <windows.h>
#include <process.h>
#include <conio.h>
#include <MMSystem.h>

using namespace std;

#include "core.h"
#include "helpers.h"

int main(void)
{
	Player players[2];
	char matrix[][SIZE] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
	int init_turn = 0, winner;

	cout << "\t\t\tTIC TAC TOE v5.4\n";

	if (!temp_is_empty(F_SAVE))
	{
		ifstream file(F_SAVE);
		char temp;
		cout << "Do you wish to continue last game (Y/N)?\n";
		cin >> temp;
		if (temp == 'Y' || temp == 'y')
			temp_load(players, &init_turn, matrix);
		else
			initialize(players);
		file.close();
	}
	else
		initialize(players);

	// functionality of game
	winner = game_engine(players, init_turn, matrix);
	
	// print the result. `winner` is the number (0 or 1) of the player. if winner is -1, then it's a draw
	if (winner != -1)
		declare_result(SUCCESS, players[winner].name);
	else
		declare_result(DRAW, "");

	// save history
	save_history(winner, players, matrix);

	// clear temporary data
	temp_clear();

	system("pause");
	return 0;
}