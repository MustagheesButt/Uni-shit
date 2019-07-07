#pragma once

#define F_SAVE "SaveData.txt"
#define SUCCESS 0
#define DRAW 1

void gotoxy(int x, int y);

void clear_line();

int write_matrix(ofstream &file, char matrix[][SIZE]);

string temp_save(Player players_array[], int turn, char array[][SIZE]);

string temp_clear();

bool temp_is_empty(string file);

string temp_load(Player players[], int* turn, char game_matrix[][SIZE]);

int declare_result(int result, string name);

int save_history(int result, Player players[], char game_matrix[][SIZE]);

int show_history();