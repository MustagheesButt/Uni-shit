//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int transition_table[7][2] = {
//	{1, 4},
//	{1, 2},
//	{3, 2},
//	{3, 2},
//	{5, 4},
//	{5, 6},
//	{5, 6}
//};
//
//int final_states_table[] = { 0, 1, 3, 4, 6 };
//
//int main(void)
//{
//	int current_state = 0;
//	string input = "010"; // input with default value
//
//	// ask for input
//	cout << "Enter a string containing only 0s and 1s: ";
//	cin >> input;
//
//	// process
//	for (int i = 0; i < input.length(); i++)
//	{
//		current_state = transition_table[current_state][input[i] - '0'];
//	}
//
//	// check if in final state
//	bool status = false;
//
//	for (int i = 0; i < sizeof(final_states_table) / sizeof(int); i++)
//	{
//		if (current_state == final_states_table[i])
//		{
//			status = true;
//			break;
//		}	
//	}
//
//	// output
//	cout << input;
//	if (status)
//	{
//		cout << " accepted!\n";
//	}
//	else
//	{
//		cout << " NOT accepted!\n";
//	}
//
//	return 0;
//}