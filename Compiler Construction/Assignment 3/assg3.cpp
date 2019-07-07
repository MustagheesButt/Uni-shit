/* output class tokens
* Identifiers and numbers only + errors
*/
#include <iostream>
#include <string>
#include <vector>

#include "Specification.h"

using namespace std;

/* CONSTS */
const int MAX_LOOKAHEAD_ALLOWED = 1;

/* helpers */
template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n + 1;

	std::vector<T> vec(first, last);
	return vec;
}

vector<char> merge(const vector<char> &left, const vector<char> &right)
{
	vector<char> result;
	auto lit = left.begin();
	auto rit = right.begin();
	while (lit != left.end() || rit != right.end()) {
		bool lft = false;
		if (rit == right.end())
			lft = true;
		else {
			if (lit != left.end())
				lft = *lit < *rit;
		}
		result.push_back(lft ? *lit++ : *rit++);
	}
	return result;
}

bool dfa_accepts(vector<vector<pair<vector<char>, int> > > dfa, vector<int> accepting_states, string input, int pos, int token_length, int look_ahead)
{
	for (int x = 0; x <= look_ahead; x++)
	{
		int state = 0;
		for (int i = pos; i < pos + token_length + x; i++)
		{
			bool found = false;

			for (auto j : dfa[state])
			{
				for (auto k : j.first)
					if (k == input[i])
					{
						found = true;
						state = j.second;
						break;
					}

				if (found)
					break;
			}	

			if (!found)
				return false;
		}

		for (auto i : accepting_states)
			if (i == state)
				return true;
	}	

	return false;
}

/* char sets */
vector<char> ALPHA = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
vector<char> DIGITS = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
vector<char> NUMBER_SPECIALS = {'.', 'e', 'E'};
vector<char> IDENTIFIER_SPECIALS = {'_'};
vector<char> ERRORS = { '$', '@', '.' };

/* specifications */
/* specification => (DFA, DFA accepting states, look_ahead(optional)) */
Specification Identifier(
	{
		{
			{merge(ALPHA, IDENTIFIER_SPECIALS), 1} // what input it accepts, which state it goes to
		},
		{
			{merge(merge(ALPHA, IDENTIFIER_SPECIALS), DIGITS), 1}
		}
	}, { 1 }
);

vector<char> DOT = slice(NUMBER_SPECIALS, 0, 0);
Specification Number(
	{
		{
			{DIGITS, 1},
			{DOT, 3} // dot
		},
		{
			{DIGITS, 1},
			{DOT, 2}, // dot
			{slice(NUMBER_SPECIALS, 1, 2), 5} // e | E
		},
		{
			{DIGITS, 2},
			{slice(NUMBER_SPECIALS, 1, 2), 5} // e | E
		},
		{
			{DIGITS, 4}
		},
		{
			{DIGITS, 4},
			{slice(NUMBER_SPECIALS, 1, 2), 5}
		},
		{
			{DIGITS, 6}
		},
		{
			{DIGITS, 6}
		}
	}, { 1, 2, 4, 6 }, 1
);

Specification Error(
	{
		{
			{ERRORS, 1}
		},
		{
			{ERRORS, 1}
		}
	}, { 1 }
);


vector<Specification> SPECIFICATIONS = {
	Identifier,
	Number,
	Error
};

int main(void)
{
	string input = "123";

	cout << "Enter a string: ";
	cin >> input;

	for (int i = 0; i < input.length(); i++)
	{
		// 1. check preference (the first spec satisfied)
		string token_class;
		string token;

		for (int j = 0; j < SPECIFICATIONS.size(); j++)
		{
			if (dfa_accepts(SPECIFICATIONS[j].DFA, SPECIFICATIONS[j].DFA_accepting_states, input, i, 1, SPECIFICATIONS[j].look_ahead))
			{
				switch (j)
				{
				case 0:
					token_class = "IDENTIFIER";
					break;
				case 1:
					token_class = "NUMBER";
					break;
				case 2:
					token_class = "ERROR";
					break;
				default:
					token_class = "ERROR";
					break;
				}

				token = input[i];

				// 2. maximal munch
				int starts_from = i;
				while (i < input.length() - 1 && dfa_accepts(SPECIFICATIONS[j].DFA, SPECIFICATIONS[j].DFA_accepting_states, input, starts_from, token.length(), SPECIFICATIONS[j].look_ahead))
				{
					token += input[++i];
				}

				if (!dfa_accepts(SPECIFICATIONS[j].DFA, SPECIFICATIONS[j].DFA_accepting_states, input, starts_from, token.length(), SPECIFICATIONS[j].look_ahead))
				{
					token.pop_back();
					--i;
				}
			}	

			// once found token break out of finding correct specification loop
			if (token_class.length() > 0)
				break;
		}

		// output TOKEN, TOKEN_CLASS
		cout << token << ", " << token_class << '\n';
	}
	
	//if (dfa_accepts(NUMBER, NUMBER_ACCEPTING_STATES, input))
	//	cout << "accepted!\n";
	//else
	//	cout << "rejected!\n";

	return 0;
}