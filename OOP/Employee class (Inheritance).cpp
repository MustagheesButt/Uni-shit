#include"iostream"
#include"string"
using namespace std;

class Employee
{
	string ssn;
	string f_name;
	string l_name;

public:

	//CONSTRUCTOR
	Employee(string f, string l, string ssn)
	{
		f_name = f;
		l_name = l;
		this->ssn = ssn;
	}

	//setter and getter for first name
	void set_f_name(string f)
	{
		f_name = f;
	}

	string get_f_name()
	{
		return f_name;
	}

	//setter and getter for last name
	void set_l_name(string f)
	{
		l_name = f;
	}

	string get_l_name()
	{
		return l_name;
	}

	//setter and getter for SSN
	void set_ssn_name(string ssn)
	{
		ssn = ssn;
	}

	string get_ssn()
	{
		return ssn;
	}

	virtual void print()
	{
		cout << "The name of the employee is : " << f_name << ' ' << l_name<<endl;
		cout << "SSN : " << ssn << endl;
	}

	virtual double earnings() = 0;
};

class SalariedEmployee : public Employee
{
private:
	double weeklySalary;

public:
	SalariedEmployee(string ssn, string first_name, string last_name, double weeklySalary = 0) : Employee(ssn, first_name, last_name)
	{
		this->weeklySalary = weeklySalary;
	}
	// get set
	void set_weeklySalary(double ws)
	{
		this->weeklySalary = ws;
	}
	double get_weeklySalary() const
	{
		return this->weeklySalary;
	}

	// virtual print
	void print()
	{
		Employee::print();
		cout << "Weekly Salary: " << this->weeklySalary << endl;
	}

	double earnings()
	{
		return this->weeklySalary;
	}
};

class HourlyEmployee : public Employee
{
private:
	double wage;
	double hours;

public:
	HourlyEmployee(string ssn, string first_name, string last_name, double wage = 0, double hours = 0) : Employee(ssn, first_name, last_name)
	{
		this->wage = wage;
		this->hours = hours;
	}
	// get set
	void set_wage(double wage)
	{
		this->wage = wage;
	}
	double get_wage() const
	{
		return this->wage;
	}

	void set_hours(double hours)
	{
		this->hours = hours;
	}
	double get_hours() const
	{
		return this->hours;
	}

	// virtual print
	void print()
	{
		Employee::print();
		cout << "Wage: " << this->wage << endl;
		cout << "Hours: " << this->hours << endl;
	}

	double earnings()
	{
		return this->wage * this->hours;
	}
};

class CommissionEmployee : public Employee
{
	double gross_sales;
	double com_rate;

public:
	//constructor
	CommissionEmployee(string ssn, string first_name, string last_name, double a = 0.0, double b = 0.0) : Employee(ssn, first_name, last_name)
	{
		gross_sales = a;
		com_rate = b;
	}

	//setter and getter for gross saales
	void set_sales(double a)
	{
		gross_sales = a;
	}
	double get_sales()
	{
		return gross_sales;
	}

	//setter and getter for commision
	void set_commision(double a)
	{
		com_rate = a;
	}
	double get_commision()
	{
		return com_rate;
	}

	void print()
	{
		Employee::print();
		cout << "the gross pay is : " << gross_sales << endl;
		cout << "The commision rate is : " << com_rate << endl;
	}

	double earnings()
	{
		return (gross_sales * com_rate);
	}
};


class BasePlusCommissionEmployee : public CommissionEmployee
{
	double base_salary;

public:
	//constructor
	BasePlusCommissionEmployee(string ssn, string first_name, string last_name, double gross_sales = 0, double com_rate = 0, double base = 0) : CommissionEmployee(ssn, first_name, last_name, gross_sales, com_rate)
	{
		base_salary = base;
	}

	//setter and getter for gross saales
	void set_base_salary(double a)
	{
		base_salary = a;
	}
	double get_sales()
	{
		return base_salary;
	}


	void print()
	{
		CommissionEmployee::print();
		cout << "the base salary is : " << base_salary << endl;
	}

	double earnings()
	{
		return (CommissionEmployee::earnings() + base_salary);
	}
};

int main(void)
{
	SalariedEmployee se("123", "don", "omar", 100);
	HourlyEmployee he("321", "bon", "creek", 12, 36);
	CommissionEmployee ce("423", "jon", "clay", 9, 2500);
	BasePlusCommissionEmployee bce("523", "ron", "vayne", 9, 1500, 10000);

	Employee* eptr[4];
	eptr[0] = &se;
	eptr[1] = &he;
	eptr[2] = &ce;
	eptr[3] = &bce;

	for (int i = 0; i < 4; i++)
	{
		eptr[i]->print();
		eptr[i]->earnings();
	}

	return 0;
}