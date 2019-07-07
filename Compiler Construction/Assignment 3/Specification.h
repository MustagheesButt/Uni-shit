#pragma once
#include <vector>

class Specification
{
public:
	std::vector<std::vector<std::pair<std::vector<char>, int> > > DFA;
	std::vector<int> DFA_accepting_states;

	int look_ahead;

	Specification(std::vector<std::vector<std::pair<std::vector<char>, int> > >, std::vector<int>, int look_ahead = 0);
	~Specification();
};

