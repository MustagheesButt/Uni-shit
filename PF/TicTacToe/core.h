#pragma once

#define SIZE 3

struct Player {
	string name;
	int id;
};

int initialize(Player players_array[]);

int game_engine(Player players_array[], int init_turn, char array[][SIZE]);

int ask_choice(Player player, char game_matrix[][SIZE]);

void show_table(char array[][SIZE]);

bool check(char b[SIZE][SIZE], int row, int col, int dr, int dc);