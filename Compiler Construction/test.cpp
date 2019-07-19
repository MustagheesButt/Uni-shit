//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//vector<char> alphbts = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
//vector<char> dgts = { '0','1','2','3','4','5','6','7','8','9' };
//vector<char> spcls1 = { '_' };
//vector<char> spcls2 = { '.' };
//vector<char> spcls3 = { 'e','E' };
//vector<char> errs = { '$','@' };
//
//bool dfa_for_identifiers(string input)
//{
//	int transTable_for_identifiers[3][3] =
//	{
//		//s,a,d
//		{ 1,1,2 },
//	{ 1,1,1 },
//	{ 2,2,2 }
//	};
//	vector<int> idntfr_accpt_state = { 1 };
//
//	int curState = 0;
//	for (int i = 0; i < input.length(); i++)
//	{
//		int found = -1;
//		for (auto j : alphbts)
//		{
//			if (j == input[i])
//				found = 1;
//		}
//		for (auto j : spcls1)
//		{
//			if (j == input[i])
//				found = 0;
//		}
//		for (auto j : dgts)
//		{
//			if (j == input[i])
//				found = 2;
//		}
//		if (found == -1)
//			return false;
//		curState = transTable_for_identifiers[curState][found];
//	}
//	for (auto k : idntfr_accpt_state)
//	{
//		if (curState == k)
//			return true;
//	}
//	return false;
//}
//
//bool dfa_for_numbers(string input)
//{
//	int transTable_for_numbers[8][3] =
//	{
//		//d,.,e
//		{ 1,4,7 },
//	{ 1,2,6 },
//	{ 2,7,6 },
//	{ 3,7,7 },
//	{ 5,7,7 },
//	{ 5,7,6 },
//	{ 3,7,7 },
//	{ 7,7,7 }
//	};
//	vector<int> number_accpt_state = { 1,2,3,5 };
//
//	int curState = 0;
//	for (int i = 0; i < input.length(); i++)
//	{
//		int found = -1;
//		for (auto j : dgts)
//		{
//			if (j == input[i])
//				found = 0;
//		}
//		for (auto j : spcls2)
//		{
//			if (j == input[i])
//				found = 1;
//		}
//		for (auto j : spcls3)
//		{
//			if (j == input[i])
//				found = 2;
//		}
//		if (found == -1 || curState == 7)
//			return false;
//		curState = transTable_for_numbers[curState][found];
//	}
//	for (auto k : number_accpt_state)
//	{
//		if (curState == k)
//			return true;
//	}
//	return false;
//}
//
//vector<char> combine(vector<char> v1, vector<char> v2)
//{
//	vector<char> combination;
//	for (auto i : v1)
//		combination.push_back(i);
//	for (auto i : v2)
//		combination.push_back(i);
//	return combination;
//}
//
//int checkSpec(string str, string token, int k)
//{
//	vector<char> identf = combine(combine(alphbts, spcls1), dgts);
//	vector<char> num = combine(combine(dgts, spcls2), spcls3);
//	for (auto i : num)
//	{
//		if (str[k] == 'e' || str[k] == 'E')
//		{
//			if (k == 0)
//				break;
//			bool found = false;
//			for (auto j : dgts)
//			{
//				if (str[k + 1] == j)
//				{
//					found = true;
//					break;
//				}
//			}
//			if (found == false)
//				break;
//		}
//		if (str[k] == '.')
//		{
//			if (k != 0)
//			{
//				bool found1 = false;
//				bool found2 = false;
//				for (auto l : dgts)
//				{
//					if (str[k + 1] == l)
//						found1 = true;
//					if (str[k - 1] == l)
//						found2 = true;
//				}
//
//				if (!found1 && !found2)
//				{
//					return 2;
//				}
//				if (token[0] == '.' && found1 == false)
//				{
//					return 2;
//				}
//				if (token[0] == '.' && k == str.length() - 1)
//				{
//					return 2;
//				}
//			}
//			else
//			{
//				bool found1 = false;
//				for (auto l : dgts)
//				{
//					if (str[k + 1] != l)
//						found1 = true;
//				}
//				if (found1)
//					return 2;
//			}
//		}
//		if (str[k] == i)
//			return 1;
//	}
//	for (auto i : identf)
//	{
//		if (str[k] == i)
//			return 0;
//	}
//	for (auto i : errs)
//	{
//		if (str[k] == i)
//			return 2;
//	}
//	return 3;
//}
//
//int main()
//{
//	string input;
//	cout << "enter input string:" << '\n';
//	getline(cin, input);
//
//	for (int i = 0; i < input.length(); i++)
//	{
//		string type;
//		string token;
//		token.push_back(input[i]);
//		while (true)
//		{
//			int spec = checkSpec(input, token, i);
//
//			if (spec == 0)
//			{
//				type = " identifier";
//				while (i < input.length() - 1 && dfa_for_identifiers(token))
//				{
//					if (input[i + 1] == '.')
//					{
//						token += input[++i];
//						break;
//					}
//					token += input[++i];
//				}
//
//				if (!dfa_for_identifiers(token))
//				{
//					token.pop_back();
//					--i;
//				}
//				break;
//			}
//			else if (spec == 1)
//			{
//				type = " number";
//				if (token[0] == '.')
//					token += input[++i];
//				while (i < input.length() - 1 && dfa_for_numbers(token))
//				{
//					if (input[i + 1] == 'e' || input[i + 1] == 'E')
//						token += input[++i];
//					token += input[++i];
//				}
//
//				if (!dfa_for_numbers(token))
//				{
//					if (i != 0)
//					{
//						if (input[i - 1] == 'e' || input[i - 1] == 'E')
//						{
//							token.pop_back();
//							--i;
//						}
//						token.pop_back();
//						--i;
//					}
//				}
//				break;
//			}
//			else if (spec == 2)
//			{
//				type = " error";
//				break;
//			}
//			else if (spec == 3)
//			{
//				type = " unspecified";
//				break;
//			}
//		}
//
//		cout << '\n' << token << " :" << type << '\n';
//	}
//
//	return 0;
//}