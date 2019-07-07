#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Student
{
	friend class StudentList;
private:
	int id; //id of a student.
	string name; //name of a student.
	float cgpa; //cgpa of a student.
	Student *next; //address of the next available object.

public:
	Student(int id, string name, float cgpa, Student *next)
	{
		this->id = id;
		this->name = name;
		this->cgpa = cgpa;
		this->next = next;
	}
};

class StudentList
{
private:
	Student *head; //start of the list
	Student *cursor; //current item of the list

public:
	StudentList()
	{
		this->head = NULL;
		this->cursor = NULL;
	}
	~StudentList()
	{
		Student* iterator = this->head;

		do
		{
			Student* temp = iterator;
			iterator = iterator->next;
			delete temp;
		} while (iterator != NULL);
	}

	void insert(const Student& std)
	{
		Student* temp = new Student(std);

		if (this->isEmpty())
		{
			this->head = temp;
			this->cursor = temp;

			return;
		}

		if (this->cursor->next != NULL)
		{
			temp->next = this->cursor->next;
		}

		this->cursor->next = temp;
		this->cursor = temp;
	}

	void remove(int key)
	{
		if (this->isEmpty())
		{
			cout << "Failed to remove.\n";
			return;
		}

		Student* iterator = this->head;
		Student* preIterator = this->head;

		do
		{
			if (iterator->id == key)
			{
				if (iterator == this->head) // first
				{
					this->head = iterator->next;
				}
				else if (iterator->next == NULL) // last item
				{
					this->cursor = this->head;
					preIterator->next = NULL;
				}
				else if (iterator == this->cursor)
				{
					this->cursor = iterator->next;
					preIterator = iterator->next;
				}
				else
				{
					preIterator->next = iterator->next;
				}

				delete iterator;
				return;
			}

			if (iterator != this->head)
				preIterator = preIterator->next;
			iterator = iterator->next;
		} while (iterator != NULL);
	}

	void search(float cgpa) const
	{
		if (this->isEmpty())
		{
			cout << "List is empty!\n";
			return;
		}

		Student* iterator = this->head;
		do
		{
			if (iterator->cgpa == cgpa)
				cout << "ID: " << iterator->id << ", Name: " << iterator->name << ", CGPA: " << iterator->cgpa << endl;

			iterator = iterator->next;
		} while (iterator != NULL);
	}

	void replace(const Student& newStd)
	{
		if (this->isEmpty())
		{
			this->insert(newStd);
			return;
		}

		Student* iterator = this->head;

		do
		{
			if (iterator->id == newStd.id)
			{
				iterator->name = newStd.name;
				iterator->cgpa = newStd.cgpa;
			}

			iterator = iterator->next;
		} while (iterator != NULL);
	}

	bool isEmpty() const
	{
		return this->cursor == NULL;
	}

	void gotoBeginning()
	{
		this->cursor = this->head;
	}

	void gotoEnd()
	{
		if (!this->isEmpty())
			while (cursor->next != NULL)
				cursor = cursor->next;
	}

	bool gotoNext()
	{
		if (this->cursor->next != NULL)
		{
			this->cursor = this->cursor->next;
			return true;
		}

		return false;
	}

	bool gotoPrior()
	{
		Student* iterator = this->head;

		do
		{
			if (iterator->next == this->cursor)
			{
				this->cursor = iterator;
				return true;
			}
			iterator = iterator->next;
		} while (iterator != NULL);

		return false;
	}

	Student getCursor()
	{
		return *(this->cursor);
	}

	void show_structure() const
	{
		if (this->isEmpty())
		{
			cout << "List is empty!\n";
			return;
		}

		Student* iterator = this->head;
		do
		{
			cout << "ID: " << iterator->id << ", Name: " << iterator->name << ", CGPA: " << iterator->cgpa << endl;

			iterator = iterator->next;
		} while (iterator != NULL);
	}
};

int main(void)
{
	fstream in_file("input.txt");

	StudentList my_list;

	while (true)
	{
		int id; string name; float cgpa;
		
		in_file >> id; in_file.ignore();

		if (in_file.eof())
			break;

		getline(in_file, name);

		in_file >> cgpa;

		//cout << id << ' ' << name << endl;

		Student std(id, name, cgpa, NULL);

		my_list.insert(std);
	}

	my_list.show_structure();

	int r_id;
	cout << "Enter ID to remove: ";
	cin >> r_id;
	my_list.remove(r_id);
	cout << '\n' << "Removing " << r_id << "th\n";

	my_list.show_structure();

	float s_cgpa;
	cout << "Search for CGPA: ";
	cin >> s_cgpa;
	cout << '\n' << "Searching for CGPA = " << s_cgpa << ":\n";
	my_list.search(s_cgpa);

	in_file.close();

	return 0;
}