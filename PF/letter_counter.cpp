#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,iee=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0;
	int q=0,r=0,s=0,t=0,u=0,v=0,w=0,x=0,y=0,z=0,line=-1;
	 
    ofstream outFile("textout.txt");
	ifstream inFile("textin.txt");

	while (!inFile.eof())
	{
		
		string str = " ";
		getline(inFile, str);
		line++;
	 	
		for (int i = 0; i < str.length(); i++)
		{
	    
		    if (str[i]=='a' || str[i]=='A')
	       		a++;
	     	else if (str[i]=='b' || str[i]=='B')
	       		b++;
			else if (str[i]=='c' || str[i]=='C')
	       		c++;
			else if (str[i]=='d' || str[i]=='D')
	       		d++;
			else if (str[i]=='e' || str[i]=='E')
	        	e++;
			else if (str[i]=='f' || str[i]=='F')
	       		f++;
			else if (str[i]=='g' || str[i]=='G')
	       		g++;	
			else if (str[i]=='h' || str[i]=='H')
	       		h++;
			else if (str[i]=='i' || str[i]=='I')
	       		iee++;
			else if (str[i]=='j' || str[i]=='J')
	       		j++;
			else if (str[i]=='k' || str[i]=='K')
	       		k++;
			else if (str[i]=='l' || str[i]=='L')
	       		l++;
			else if (str[i]=='m' || str[i]=='M')
	       		m++;
			else if (str[i]=='n' || str[i]=='N')
	       		n++;
			else if (str[i]=='o' || str[i]=='O')
	       		o++;
		    else if (str[i]=='p' || str[i]=='P')
	       		p++;
		    else if (str[i]=='q' || str[i]=='Q')
	       		q++;
			else if (str[i]=='r' || str[i]=='R')
	       		r++;
			else if (str[i]=='s' || str[i]=='S')
	       		s++;
			else if (str[i]=='t' || str[i]=='T')
	       		t++;
			else if (str[i]=='u' || str[i]=='U')
	       		u++;
			else if (str[i]=='v' || str[i]=='V')
	       		v++;
			else if (str[i]=='w' || str[i]=='W')
	       		w++;
			else if (str[i]=='x' || str[i]=='X')
	       		x++;
			else if (str[i]=='y' || str[i]=='Y')
	       		y++;
			else if (str[i]=='z' || str[i]=='Z')
	       		z++;
		}
	}

    outFile << "Number of line =" << line << endl;
    outFile << "A count =" << a << endl;
    outFile << "B count =" << b << endl;
    outFile << "C count =" << c << endl;
    outFile << "D count =" << d << endl;
    outFile << "E count =" << e << endl;
    outFile << "F count =" << f << endl;
    outFile << "G count =" << g << endl;
    outFile << "H count =" << h << endl;
    outFile << "I count =" << iee << endl;
    outFile << "J count =" << j << endl;
    outFile << "k count =" << k << endl;
    outFile << "L count =" << l << endl;
    outFile << "M count =" << m << endl;
    outFile << "N count =" << n << endl;
    outFile << "O count =" << o << endl;
    outFile << "P count =" << p << endl;
    outFile << "Q count =" << q << endl;
    outFile << "R count =" << r << endl;
    outFile << "S count =" << s << endl;
    outFile << "T count =" << t << endl;
    outFile << "U count =" << u << endl;
    outFile << "V count =" << v << endl;
    outFile << "W count =" << w << endl;
    outFile << "X count =" << x << endl;
    outFile << "Y count =" << y << endl;
    outFile << "Z count =" << z << endl;
    
    inFile.close();
	outFile.close();

	return 0;
    
}
