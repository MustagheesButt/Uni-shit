#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Contact
{
	string fname; // max 15 chars
	string lname; // max 15 chars
	long number1;
	long number2;
	string email;
};

int search(string name);
int search_phone_num(string phone_num);
int search_by_letter(char letter);
int get_contact_at(int index);
int insert_record(string* first_name, string* last_name, long* number1, long* number2, string* email, int email_size);

int main(void)
{	
	int choice = 0;
	char c, ch;

	do
	{
		cout << "\n******** Phone Book *********\n";
		cout << "1) Search by first/last/full name\n";
		cout << "2) Search by letter\n";
		cout << "3) Search by number\n";
		cout << "4) Enter a Contact\n";
		cout << "5) Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		
		if (choice == 1)
		{
			string name;
			cout << "Enter first/last/full name: ";
			cin >> name;
			search(name);
		}
		else if (choice == 2)
		{
			char letter;
			cout << "Enter letter: ";
			cin >> letter;
			search_by_letter(letter);
		}
		else if (choice == 3)
		{
			string number;
			cout << "Enter phone number (without - or spaces): ";
			cin >> number;
			search_phone_num(number);
		}
		else if (choice == 4)
		{
			Contact contact;
			cout << "Enter first name, last name, Ph. Number 1, Ph. Number 2, Email address\n";
			cin >> contact.fname >> contact.lname >> contact.number1
			>> contact.number2 >> contact.email;
			insert_record(&contact.fname, &contact.lname, &contact.number1, &contact.number2, &contact.email, contact.email.size());
		}
		else if (choice == 5)
		{
			cout << "Are you sure to exit ?\n If YES press 'y' else press 'n' : ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				exit(0);
		}
		cout << "Do you Want Search any other Contact : \n If YES press 'y' else press 'n' : ";
		cin >> c;
	}
	while (c == 'y' || c == 'Y');
	
	return 0;
}

int search(string name) // searches for first, last or full name
{
	ifstream file("names.txt");
	
	if (!file.is_open())
	{
		cout << "File could not be opened! It probably does not exists.\n";
		file.close();
		return -1;
	}
	string f_name, l_name;
	int counter = 0;
	while (!file.eof())
	{
		file >> f_name >> l_name;
		if (name == f_name || name == l_name || name == f_name + ' ' + l_name)
		{
			cout << f_name << endl << l_name << endl;
			get_contact_at(counter);
			file.close();
			return 0;
		}
		counter++;
	}
	file.close();
	return -1;
}
int search_by_letter(char letter)
{
	ifstream file("names.txt");
	
	if (!file.is_open())
	{
		cout << "File could not be opened! It probably does not exists.\n";
		file.close();
		return -1;
	}
	string f_name, l_name;
	int counter = 0;
	while (!file.eof())
	{
		file >> f_name >> l_name;
		if (letter == f_name[0])
		{
			cout << f_name << endl;
			cout << l_name << endl;
			get_contact_at(counter);
			file.close();
			return 0;
		}
		else if (letter == l_name[0])
		{
			cout << f_name << endl;
			cout << l_name << endl;
			get_contact_at(counter);
			file.close();
			return 0;
		}
		counter++;
	}
	cout << "Nothing was found!\n";
	file.close();
	return -1;
}
int search_phone_num(string phone_num)
{
	ifstream file("contacts.dat", ios::binary);
	if (!file.is_open())
	{
		cout << "The file contacts.dat could not be opened. It probably does not exists.\n";
		file.close();
		return -1;
	}
	
	long num;
	int counter = 0;
	while (true)
	{
		// read first phone number
		cout << "workin!\n";
		file.read((char*)&num, 4);
		cout << num << endl;
		if (phone_num == to_string(num))
		{
			cout << "Found phone number (1st)!\n";
			file.close();
			return 0;
		}
		else
		{
			if ( string(num).find(phone_num) != string::npos )
				cout << "Found in 1st, at " << counter << endl;
		}
		// read second number
		file.read((char*)&num, 4);
		if (phone_num == string(num))
		{
			cout << "Found phone number (2nd)!\n";
			file.close();
			return 0;
		}
		else
		{
			if ( string(num).find(phone_num) != string::npos )
				cout << "Found in 2nd, at " << counter << endl;
		}
		// read length of email
		int e_len;
		file.read((char*)&e_len, sizeof(int));
		// skip email
		file.seekg(e_len, ios::cur);
		
		counter++;
		if (!file)
			break;
	}
	cout << "Given phone number was not found in contacts!\n";
	file.close();
	return -1;
}
int get_contact_at(int index)
{
	ifstream file("contacts.dat", ios::binary);
	if (!file.is_open())
	{
		cout << "The file contacts.dat could not be opened. It probably does not exists.\n";
		file.close();
		return -1;
	}
	
	int counter = 0;
	Contact cont;
	while (counter <= index)
	{
		if (!file)
			break;
		// read whole contact at once
		file.read((char*)&cont.number1, sizeof(long));
		file.read((char*)&cont.number2, sizeof(long));
		
		int e_len;
		file.read((char*)&e_len, sizeof(int));
		
		// taken from internet
		char* temp = new char[e_len + 1];
		file.read(temp, e_len);
		temp[e_len] = '\0';
		cont.email = temp;
		delete[] temp;
		
		counter++;
	}
	cout << "Phone number 1: " << cont.number1 << "\nPhone number 2: " << cont.number2 << "\nEmail address: " << cont.email << endl;
	file.close();
	return 0;
}
int insert_record(string* first_name, string* last_name, long* number1, long* number2, string* email, int email_size)
{
	if (search(*first_name + ' ' + *last_name) == 0)
	{
		cout << "Record for the given name already exists!\n";
		return -1;
	}
	else
	{
		// write to names.txt
		ofstream file("names.txt", ios::app | ios::out);
		file << *first_name << ' ' << *last_name << endl;
		file.close();
		// write to contacts.dat
		file.open("contacts.dat", ios::binary | ios::app);
		file.write((char*)number1, sizeof(long));
		file.write((char*)number2, sizeof(long));
		
		int len = email_size;
		cout << email_size << endl;
		file.write((char*)&len, sizeof(int));
		file << *email;
		
		file.close();
		cout << "Contact entered successfully!\n";
	}
	return 0;
}
