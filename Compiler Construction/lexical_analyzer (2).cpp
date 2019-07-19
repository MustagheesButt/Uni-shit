/*
* Specification independent lexical analyzer
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Token {
public:
	string lexeme;
	string token_class;
	int line_number;

	Token(string lexeme, string token_class, int line_number)
	{
		this->lexeme = lexeme;
		this->token_class = token_class;
		this->line_number = line_number;
	}
};

class Lexer {
	// external data
	string input;
	unordered_map<string, vector<int> > table;
	unordered_map<int, string> final_state_map;

	// internal data
	vector<Token> tokens;
	int token_counter = 0;

	vector<pair<string, string> > symbol_to_symbol_class_table = {
		{ "abcdefghijklmnopqrstuvwxyz", "ALPHA" },
		{ "0123456789", "DIGIT" },
		{ "eE", "eE" },
		{ " \n\t\b", "BLNKSPC" }
	};

	/*
	* Some characters may belong to more than one class (like e/E is in both alphabets and numbers)
	*/
	vector<string> get_symbol_classes(char symbol)
	{
		vector<string> temp;

		for (auto i : this->symbol_to_symbol_class_table)
		{
			for (auto j : i.first)
			{
				if (j == symbol)
				{
					temp.push_back(i.second);
				}
			}
		}

		return temp;
	}

	/*
	* Checks if a state is final
	*/
	bool is_final(int state)
	{
		if (this->final_state_map.find(this->table["ACCP"][state]) == this->final_state_map.end())
		{
			return false;
		}

		return true;
	}

	// tokenizes the `input` and stores all tokens in `tokens`
	int tokenize(string input)
	{
		int lexeme_start = 0;
		int last_scene_final_state = -1;
		int current_state = 0;
		int forward = 0;
		int remember = -1;
		int line_number = 0;

		do
		{
			vector<string> possible_symbol_classes = this->get_symbol_classes(input[forward]);

			if (possible_symbol_classes.empty())
			{
				possible_symbol_classes.push_back("");
				possible_symbol_classes[0] += input[forward];
			}

			for (string current_symbol_class : possible_symbol_classes)
			{
				//cout << "CURR SYM CLASS: " << current_symbol_class << endl;
				int next_possible_state = this->table[current_symbol_class][current_state];

				if (next_possible_state != -1)
				{
					/*
					* Generate a token. First tries to maximal munch, if -1 is found, generates a token.
					*/
					string possible_symbol_class;
					do
					{
						forward += 1;
						if (this->is_final(current_state))
						{
							last_scene_final_state = current_state;
							remember = forward - 1;
						}

						current_state = next_possible_state;	

						vector<string> _possible_symbol_classes = this->get_symbol_classes(input[forward]);

						for (string i : _possible_symbol_classes)
						{
							next_possible_state = this->table[i][current_state];
							if (next_possible_state != -1)
							{
								possible_symbol_class = i;
								break;
							}
						}

						if (next_possible_state == -1)
						{
							forward += 1;
							break;
						}
						// TODO: need to implement look-ahead somewhere where it is in non-final state
					} while (forward < input.length());

					break; // break out of the possible_symbol_classes loop
				}
				else
				{
					break;
				}
			}

			string lexeme = input.substr(lexeme_start, forward - lexeme_start);
			string token_class = this->final_state_map[this->table["ACCP"][current_state]];
			this->tokens.push_back(Token(lexeme, token_class, line_number));

			lexeme_start = forward;
			last_scene_final_state = -1;
			current_state = 0;
		} while (forward < input.length());

		return 0;
	}

public:
	Lexer(string input)
	{
		this->input = input;
	}

	Lexer(string input, unordered_map<string, vector<int> > table, unordered_map<int, string> final_state_map)
	{
		this->input = input;
		this->table = table;
		this->final_state_map = final_state_map;

		//this->tokenize(this->input);
	}

	int load_table_from_file(string file_name)
	{
		ifstream in_file(file_name);

		if (!in_file.is_open())
		{
			cout << "Could not open " << file_name << endl;
			return -1;
		}

		// empty current table
		this->table.clear();

		vector<string> keys;
		vector<vector<int> > values;

		string line;
		getline(in_file, line); // reads first line

		stringstream data(line);
		string input;
		

		// first line should be keys
		while (data >> input)
		{
			keys.push_back(input);
			values.push_back({});
		}

		// next lines should be the states
		int input2;
		while (getline(in_file, line))
		{
			int counter = 0;
			stringstream data2(line);
			while (data2 >> input2)
			{
				values[counter].push_back(input2);
				counter++;
			}
		}

		in_file.close();

		// TODO: do compression or whatever on this->table
		for (int i = 0; i < keys.size(); i++)
		{
			this->table.insert({ keys[i], values[i] });
		}

		//for (auto i : this->table)
		//	cout << i.first << ' ' << i.second[0] << endl;

		return 0;
	}

	int generate_tokens()
	{
		this->tokens.clear();
		return this->tokenize(this->input);
	}

	Token get_token()
	{
		if (this->token_counter < this->tokens.size())
			this->token_counter += 1;
		else
			return Token("", "", -1);

		return this->tokens[this->token_counter - 1];
	}
};

int main(void)
{
	string input = "test";
	getline(cin, input);

	unordered_map<string, vector<int> > table = {
		{ "DIGIT"  , { 1,  1,  2,  2,  5,  5, -1,  7 } },
		{ "eE"     , {-1,  4,  4, -1, -1, -1, -1, -1 } },
		{ "."      , { 3,  2, -1, -1, -1, -1, -1, -1 } },
		{ "@"      , { 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ "BLNKSPC", { 6, -1, -1, -1, -1, -1,  6, -1 } },
		{ "_"      , { 7, -1, -1, -1, -1, -1, -1,  7 } },
		{ "ALPHA"  , { 7, -1, -1, -1, -1, -1, -1,  7 } },
		{ "ACCP"   , { 0, 101, 102, 0, 0, 103, 104, 105, 106 } }
	};

	unordered_map<int, string> final_state_map = {
		{ 101, "NUMBER" },
		{ 102, "NUMBER" },
		{ 103, "NUMBER" },
		{ 104, "WHITESPACE" },
		{ 105, "IDENTIFIER" },
		{ 106, "ERROR"}
	};

	Lexer lex(input, table, final_state_map);
	//lex.load_table_from_file("lex-table.txt");
	lex.generate_tokens();

	Token temp("", "", -1);

	do
	{
		temp = lex.get_token();

		if (temp.line_number == -1)
		{
			cout << "No more tokens!\n";
			break;
		}

		cout << "<" << temp.lexeme << ", " << temp.token_class << "> on line " << temp.line_number << endl;
	} while (true);

	return 0;
}