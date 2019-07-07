/**
 * Author: M. Mustaghees Butt
 * mustaghees99@live.com
 * 2017
 */
#include <iostream>
#include <string>
#include <ctype.h>
#include <time.h>
#include <fstream>

#define DATAFILE "data.dat"

std::string find_and_replace(std::string source, std::string const& find, std::string const& replace)
{
	for (std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}

	return source;
}

class Player
{
public:
	std::string name;
	char symbol;

	Player()
	{
		this->name = "Player 1";
		this->symbol = 'X';
	}
	Player(std::string name, char symbol)
	{
		this->name = name;
		this->symbol = symbol;
	}
};

class TicTacToe
{
private:
	int size;
	int* state;
	int turn_counter;
	Player players[2];
	bool computer;

	/* SETTERS */
	void set_symbols(char symbol1)
	{
		symbol1 = toupper(symbol1);
		if (symbol1 != 'X' && symbol1 != 'O')
			std::cout << "Invalid symbol supplied!\n";
		else
		{
			this->players[0].symbol = symbol1;
			if (symbol1 == 'X')
				this->players[1].symbol = 'O';
			else
				this->players[1].symbol = 'X';
		}
	}

	/* VIEW FUNCTIONS */
	void display() const
	{
		system("CLS");
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
				if (this->state[i * this->size + j] == this->players[0].symbol || this->state[i * this->size + j] == this->players[1].symbol)
					std::cout << char(this->state[i * this->size + j]) << '\t';
				else
					std::cout << this->state[i * this->size + j] << '\t';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	/* UTILITY FUNCTIONS */
	void input(std::string player, char symbol)
	{
		char cell;
		do
		{
			std::cout << player << " enter cell number (1 - " << this->size * this->size << "): ";
			std::cin >> cell;

			if (cell == 'S' || cell == 's')
			{
				this->save(*this);
				std::cout << "Game Saved!\n";
				system("PAUSE");
				continue;
			}

			cell = cell - '0';
			if (this->state[cell - 1] == 'O' || this->state[cell - 1] == 'X')
			{
				std::cout << "This cell has already been taken!\n";
				cell = -1;
			}
		} while (!(cell >= 1) || !(cell <= this->size * this->size));

		this->state[cell - 1] = symbol;
	}

	void run_AI(int player_id)
	{
		// checks if we can win, otherwise make a random move
		for (int i = 0; i < this->size * this->size; i++)
		{
			int temp = this->state[i];
			if (temp != this->players[0].symbol && temp != this->players[1].symbol)
			{
				this->state[i] = players[player_id].symbol;
				if (this->check_win(players[player_id].symbol)) // check if AI wins
				{
					return;
				}
				
				this->state[i] = players[(player_id + 1) % 2].symbol;
				if (this->check_win(players[(player_id + 1) % 2].symbol)) // check if Human wins
				{
					this->state[i] = players[player_id].symbol; // mark it to stop Human from winning
					return;
				}
				this->state[i] = temp;
			}
		}

		int cell;
		do
		{
			cell = rand() % (this->size * this->size);
		} while (this->state[cell] == this->players[0].symbol || this->state[cell] == this->players[1].symbol);

		this->state[cell] = players[player_id].symbol;
	}

	bool check_win_3x3(int symbol)
	{
		return is_same(this->state, symbol, 0, 1, 2) // 1st horizontal line
			|| is_same(this->state, symbol, 3, 4, 5) // 2nd horizontal line
			|| is_same(this->state, symbol, 6, 7, 8) // 3rd horizontal line
			|| is_same(this->state, symbol, 0, 3, 6) // 1st vertical line
			|| is_same(this->state, symbol, 1, 4, 7) // 2nd vertical line
			|| is_same(this->state, symbol, 2, 5, 8) // 3rd vertical line
			|| is_same(this->state, symbol, 0, 4, 8) // 1st diagonal
			|| is_same(this->state, symbol, 2, 4, 6); // 2nd diagonal
	}
	bool check_win_4x4(int symbol)
	{
		return is_same(this->state, symbol, 0, 1, 2, 3) // 1st horizontal line
			|| is_same(this->state, symbol, 4, 5, 6, 7) // 2nd horizontal line
			|| is_same(this->state, symbol, 8, 9, 10, 11) // 3rd horizontal line
			|| is_same(this->state, symbol, 12, 13, 14, 15) // 4th horizontal line
			|| is_same(this->state, symbol, 0, 4, 8, 12) // 1st vertical line
			|| is_same(this->state, symbol, 1, 5, 9, 13) // 2nd vertical line
			|| is_same(this->state, symbol, 2, 6, 10, 14) // 3rd vertical line
			|| is_same(this->state, symbol, 3, 7, 11, 15) // 4th vertical line
			|| is_same(this->state, symbol, 0, 5, 10, 15) // First diagonal
			|| is_same(this->state, symbol, 3, 6, 9, 12); // Second diagonal
	}
	bool check_win_5x5(int symbol)
	{
		return is_same(this->state, symbol, 0, 1, 2, 3, 4) // 1st horizontal line
			|| is_same(this->state, symbol, 5, 6, 7, 8, 9) // 2nd horizontal line
			|| is_same(this->state, symbol, 10, 11, 12, 13, 14) // 3rd horizontal line
			|| is_same(this->state, symbol, 15, 16, 17, 18, 19) // 4th horizontal line
			|| is_same(this->state, symbol, 20, 21, 22, 23, 24) // 5th horizontal line
			|| is_same(this->state, symbol, 0, 5, 10, 15, 20) // 1st vertical line
			|| is_same(this->state, symbol, 1, 6, 11, 16, 21) // 2nd vertical line
			|| is_same(this->state, symbol, 2, 7, 12, 17, 22) // 3rd vertical line
			|| is_same(this->state, symbol, 3, 8, 13, 18, 23) // 4th vertical line
			|| is_same(this->state, symbol, 4, 9, 14, 19, 24) // 5th vertical line
			|| is_same(this->state, symbol, 0, 6, 12, 18, 24) // First diagonal
			|| is_same(this->state, symbol, 4, 8, 12, 16, 20); // Second diagonal
	}

	bool check_win(int symbol)
	{
		if (this->size == 3)
			return this->check_win_3x3(symbol);
		else if (this->size == 4)
			return this->check_win_4x4(symbol);
		return this->check_win_5x5(symbol);
	}

	bool is_same(int arr[], int symbol, int x, int y, int z) {
		return (arr[x] == symbol && arr[y] == symbol && arr[z] == symbol);
	}
	bool is_same(int arr[], int symbol, int x, int y, int z, int a) {
		return (arr[x] == symbol && arr[y] == symbol && arr[z] == symbol && arr[a] == symbol);
	}
	bool is_same(int arr[], int symbol, int x, int y, int z, int a, int b) {
		return (arr[x] == symbol && arr[y] == symbol && arr[z] == symbol && arr[a] == symbol && arr[b] == symbol);
	}

	/* FILE HANDLERS */
	int save(TicTacToe& game)
	{
		std::fstream out_file(DATAFILE, std::ios::app);
		// write size
		out_file << this->size << ' ';

		// write state (matrix)
		for (int i = 0; i < this->size * this->size; i++)
		{
			out_file << this->state[i] << ' ';
		}

		// write turn counter
		out_file << this->turn_counter << ' ';

		// write player data
		out_file << find_and_replace(this->players[0].name, " ", "*") << ' ' << this->players[0].symbol << ' ';
		out_file << find_and_replace(this->players[1].name, " ", "*") << ' ' << this->players[1].symbol << ' ';

		// is computer
		out_file << this->computer << '\n';

		out_file.close();

		return 0;
	}

	int load(int nth_record)
	{
		std::fstream in_file(DATAFILE, std::ios::in);

		if (!in_file.is_open())
			return -1;

		// go to nth-record
		in_file.seekp(nth_record * sizeof(TicTacToe));

		// load size
		in_file >> this->size;

		// load state (matrix)
		for (int i = 0; i < this->size * this->size; i++)
		{
			in_file >> this->state[i];
		}

		// load turn counter
		in_file >> this->turn_counter;

		// load player data
		in_file >> this->players[0].name >> this->players[0].symbol;
		this->players[0].name = find_and_replace(this->players[0].name, "*", " ");
		in_file >> this->players[1].name >> this->players[1].symbol;
		this->players[1].name = find_and_replace(this->players[1].name, "*", " ");

		// is computer
		in_file >> this->computer;

		in_file.close();

		return 0;
	}

public:
	/* CONSTRUCTORS */
	TicTacToe()
	{
		this->players[1].name = "Player 2";
		this->set_symbols('X');
		this->size = 3;
		this->turn_counter = 0;
		this->computer = false;

		this->state = new int[this->size * this->size];
		for (int i = 0; i < this->size * this->size; i++)
			this->state[i] = i + 1;
	}

	// only names are custom
	TicTacToe(std::string player1_name, std::string player2_name)
	{
		this->players[0].name = player1_name;
		this->players[1].name = player2_name;
		this->set_symbols('X');
		this->size = 3;
		this->turn_counter = 0;
		this->computer = false;

		this->state = new int[this->size * this->size];
		for (int i = 0; i < this->size * this->size; i++)
			this->state[i] = i + 1;
	}

	// everything except size is custom
	TicTacToe(std::string player1_name, char symbol1, std::string player2_name)
	{
		this->players[0].name = player1_name;
		this->players[1].name = player2_name;
		this->set_symbols(symbol1);
		this->size = 3;
		this->turn_counter = 0;
		this->computer = false;

		this->state = new int[this->size * this->size];
		for (int i = 0; i < this->size * this->size; i++)
			this->state[i] = i + 1;
	}
	
	// everything including size is custom
	TicTacToe(std::string player1_name, char symbol1, std::string player2_name, int size)
	{
		this->players[0].name = player1_name;
		this->players[1].name = player2_name;
		this->set_symbols(symbol1);
		this->size = size;
		this->turn_counter = 0;
		this->computer = false;

		this->state = new int[this->size * this->size];
		for (int i = 0; i < this->size * this->size; i++)
			this->state[i] = i + 1;
	}

	// same as above except player2 is computer
	TicTacToe(std::string player1_name, char symbol1, bool computer, int size)
	{
		this->players[0].name = player1_name;
		this->players[1].name = "Computer G";
		this->set_symbols(symbol1);
		this->size = size;
		this->turn_counter = 0;
		this->computer = computer;

		this->state = new int[this->size * this->size];
		for (int i = 0; i < this->size * this->size; i++)
			this->state[i] = i + 1;
	}

	int start()
	{
		for (int& i = this->turn_counter; i < this->size * this->size; i++)
		{
			this->display();
			if (this->computer && i % 2 == 1)
				this->run_AI(1);
			else
				this->input(this->players[i % 2].name, this->players[i % 2].symbol);
			
			if (this->check_win(this->players[i % 2].symbol))
			{
				this->display();
				std::cout << this->players[i % 2].name << " has won!\n";
				return 0;
			}
		}

		std::cout << "Looks like the game is a draw! Too bad :(\n";
		return 0;
	}
};

int main(void)
{
	srand(time(NULL));

	std::string p1, p2;
	char s1, again;
	int size, sizes[3] = {3, 4, 5}, g_type;
	bool is_computer = false;

START:

	/* LOAD - DELETE - NEW menu */

	std::cout << "Select Game Type:\n\t1. Human vs Human\n\t2. Human vs Computer\n";
	std::cin >> g_type;

	// player names and symbols get decided here
	std::cout << "Enter Player 1 name: ";
	std::cin >> p1;
	do
	{
		std::cout << "Enter Player 1 Symbol (X, O): ";
		std::cin >> s1;
		s1 = toupper(s1);
	} while (s1 != 'X' && s1 != 'O');
	
	if (g_type == 1)
	{
		std::cout << "Enter Player 2 name: ";
		std::cin >> p2;
	}
	else
		is_computer = true;

	// size of board
	do
	{
		system("CLS");
		std::cout << "Select board size:\n1. 3 x 3\n2. 4 x 4\n3. 5 x 5\n";
		std::cin >> size;
	} while (size < 1 || size > 3);

	// let the games begin!
	TicTacToe* game;
	if (!is_computer)
		game = new TicTacToe(p1, s1, p2, sizes[size - 1]);
	else
		game = new TicTacToe(p1, s1, true, sizes[size - 1]);
	game->start();

	// again?
	std::cout << "Do you wanna play again? [Y/N]: ";
	std::cin >> again;

	if (again == 'Y' || again == 'y')
		goto START;

	delete game;

	system("PAUSE");
	return 0;
}
