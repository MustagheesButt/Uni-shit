#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
	string name;
	int id;
	string department;
	string position;

public:
	Employee(string _name, int _id, string _dep, string _pos)
	{
		name = _name;
		id = _id;
		department = _dep;
		position = _pos;
		cout << "Parameterized Cons..\n";
	}

	Employee(string _name, int _id)
	{
		name = _name;
		id = _id;
		department = "";
		position = "";
	}

	Employee()
	{
		name = "";
		id = 0;
		department = "";
		position = "";
	}

	Employee(const Employee &x)
	{
		name = x.name;
		id = x.id;
		department = x.department;
		position = x.position;
	}

	// getters
	string get_name()
	{
		return name;
	}

	int get_id()
	{
		return id;
	}

	string get_department()
	{
		return department;
	}

	string get_position()
	{
		return position;
	}

	// setters
	void set_name(string _name)
	{
		name = _name;
	}

	void set_id(int _id)
	{
		id = _id;
	}

	void set_department(string _dep)
	{
		department = _dep;
	}

	void set_position(string _pos)
	{
		position = _pos;
	}

	// utility methods
	void setInfo(string _name, int _id, string _dep, string _pos)
	{
		set_name(_name);
		set_id(_id);
		set_department(_dep);
		set_position(_pos);
	}
	void getInfo() // gets info from user
	{
		int _id;
		string _name, _dep, _pos;

		cout << "Enter Name: ";
		getline(cin, _name);
		set_name(_name);

		cout << "Enter ID: ";
		cin >> _id;
		set_id(_id);

		cout << "Enter Department Name: ";
		getline(cin, _dep);
		set_department(_dep);

		cout << "Enter Position Title: ";
		getline(cin, _pos);
		set_position(_pos);
	}
	void putInfo()
	{
		cout << "Name: " << name << endl;
		cout << "ID: " << id << endl;
		cout << "Department: " << department << endl;
		cout << "Position: " << position << endl;
	}

	// destructors
	~Employee()
	{
		cout << "Destructor executed...\n";
	}
};

int main(void)
{
	Employee arr[4];

	arr[0] = Employee("Ejaz Ashraf", 1230, "PUCIT - Old Campus", "Assistant Professor");
	arr[1] = Employee("Muhammad Farooq", 1231, "PUCIT - Old Campus", "Lecturer");
	arr[2] = Employee("Abdul Mateen", 1232, "PUCIT - New Campus", "Lecturer");
	arr[3] = Employee("Madiha Khalid", 1233, "PUCIT - New Campus", "Lecturer");

	for (int i = 0; i < 4; i++)
	{
		arr[i].putInfo();
	}

	system("PAUSE");
	return 0;
}
