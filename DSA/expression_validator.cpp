//#include <iostream>
//#include <string>
//#include <utility>
//#include <stack>
//
//using namespace std;
//
//char get_pair(char x)
//{
//	switch (x)
//	{
//	case ')':
//		return '(';
//	case ']':
//		return '[';
//	default:
//		break;
//	}
//
//	return NULL;
//}
//
//bool validate_expr(string expression)
//{
//	char map[256] = { 0 };
//	map['('] = '1'; map[')'] = '(';
//	map['['] = '1'; map[']'] = '[';
//	map['{'] = '1'; map['}'] = '{';
//
//	stack<char> fkin_stack;
//	
//	for (char ch : expression)
//	{
//		if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
//			if (map[ch] == '1')
//				fkin_stack.push(ch);
//			else if (fkin_stack.empty())
//				return false;
//			else if (map[ch] != 0 && fkin_stack.top() != map[ch])
//				return false;
//			else
//				fkin_stack.pop();
//	}
//
//	if (fkin_stack.empty())
//		return true;
//	else
//		return false;
//}
//
//int main(void)
//{
//	string input = "](()[])";
//
//	if (validate_expr(input))
//		cout << "Validated!\n";
//	else
//		cout << "Is invalid!\n";
//
//	return 0;
//}
