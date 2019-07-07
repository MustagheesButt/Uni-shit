#include<iostream>
using namespace std;

class Rational
{
private:
	int numerator;
	int denominator;

public:
	// constructors
	Rational(int n, int d)
	{
		numerator = n;
		set_denominator(d);
	}

	Rational(int n)
	{
		numerator = n;
		denominator = 1;
	}

	//setter and getter 
	void set_numerator(int n)
	{
		numerator = n;
	}

	int get_nummerator()
	{
		return numerator;
	}

	void set_denominator(int d)
	{
		if (d == 0)
			denominator = 1;
		else
			denominator = d;
	}

	void write()
	{
		cout << "The rational number is\n";
		cout << numerator << "/" << denominator;
	}

	void read()
	{
		char c;
		cout << "Enter rational number WITH SLASH\n";
		cin >> numerator >> c >> denominator;
	}

	Rational operator+ (const Rational &obj)
	{
			return Rational((numerator * obj.denominator + denominator * obj.numerator) / (denominator * obj.denominator));
	}

	Rational operator- (const Rational &obj)
	{
		return Rational((numerator * obj.denominator - denominator * obj.numerator) / (denominator * obj.denominator));
	}

	Rational operator*(const Rational &obj)
	{
		return Rational((numerator * obj.numerator) / (denominator * obj.denominator));
	}

	Rational operator/(const Rational &obj)
	{
		return Rational((numerator * obj.denominator) / (obj.numerator * denominator));
	}

	Rational operator-(int)
	{
		if (numerator < 0)
		{
			return(numerator = numerator);
		}

		else
			return 

	}
};