#include "Specification.h"



Specification::Specification(std::vector<std::vector<std::pair<std::vector<char>, int> > > DFA, std::vector<int> DFA_accepting_states, int look_ahead)
{
	this->DFA = DFA;
	this->DFA_accepting_states = DFA_accepting_states;

	this->look_ahead = look_ahead;
}


Specification::~Specification()
{
}
