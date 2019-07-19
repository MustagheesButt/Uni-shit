//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//string getSubStr(string input,int start,int end)
//{
//	string substr;
//	for (int i = start; i <= end; i++)
//		substr += input[i];
//	return substr;
//}
//
//int main()
//{
//	ifstream ifile("specifications.txt");
//	if (ifile.is_open())
//	{
//		string line;
//		int lines=0;
//
//		getline(ifile, line);
//		while (!ifile.eof())
//		{
//			lines++;
//			getline(ifile, line);
//		}
//		
//		int **transTable = new int*[lines];
//		for (int i = 0; i < lines; i++)
//			transTable[i] = new int[129];
//
//		ifile.clear();
//		ifile.seekg(0,ios::beg);
//		
//		int value;
//		for (int i=0; i<lines;i++)
//		{
//			for (int j=0;j<129;j++)
//			{
//				ifile >> value;
//				transTable[i][j] = value;
//			}
//		}
//
//		vector<pair<int,int>> finalStates;
//		
//		for (int i = 0; i < lines; i++)
//		{
//			if (transTable[i][128] != 0)
//			{
//				finalStates.push_back({ i, transTable[i][128] });
//			}
//		}	
//
//		ifile.close();
//
//		ifstream ifile2("program.txt");
//		if (ifile2.is_open())
//		{
//			string input;
//			char ch;
//			ifile2 >> ch;
//			while (!ifile2.eof())
//			{
//				input += ch;
//				ifile2 >> ch;
//			}
//			ifile2.close();
//
//			int lexStart=0,
//				lastSeenFS=-1,
//				currState=0,
//				remember= -1,
//				forward=0,
//				lineNo=0;
//
//			for (int i = 0; i < input.length(); i++)
//			{				
//				if (input[i] == '\n')
//					lineNo++;
//				
//				cout << currState << endl;
//				forward++;
//				currState = transTable[currState][int(input[i])];
//
//				if (currState == -1)
//				{
//					if (lastSeenFS != -1 && remember!=-1)
//					{
//						string lexeme = getSubStr(input, lexStart, remember);
//						cout << "< " << lexeme << " : " << lastSeenFS << " >\n";
//						forward = remember + 1;
//						lexStart = remember + 1;
//						lastSeenFS = -1;
//						remember = -1;
//						currState = 0;
//					}
//					else
//					{
//						cout << "error : " << input[lexStart] << "at line # " << lineNo << '\n' ;
//					}
//				}
//
//				for (auto i : finalStates)
//				{
//					if (currState == i.first)
//					{
//						lastSeenFS = i.second;
//						remember = forward - 1;
//					}
//				}	
//			}
//		}
//		else
//		{
//			cout << "nothing read...\nexiting...\n";
//			exit(0);
//		}
//	}
//	else
//	{
//		cout << "no specifications given...\nexiting...\n";
//		exit(0);
//	}
//
//	return 0;
//}