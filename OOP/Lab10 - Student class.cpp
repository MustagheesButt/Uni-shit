#include <iostream>
#include <vector>

using namespace std;

class Student
{
	int roll_num;
	double cgpa;

public:
	Student(int roll_number, double cgpa)
	{
		this->roll_num = roll_number;
		this->cgpa = cgpa;
	}

	bool operator>(Student student)
	{
		return (this->cgpa > student.cgpa) || (this->cgpa == student.cgpa && this->roll_num < student.roll_num);
	}

	bool operator<(Student student)
	{
		return (this->cgpa < student.cgpa) || (this->roll_num < student.roll_num);
	}

	static int get_parent(int i)
	{
		return (i - 1) / 2;
	}

	friend class Student_MaxHeap;
};

class Student_MaxHeap
{
private:
	vector<Student> students;

public:
	bool insert(Student student)
	{
		this->students.push_back(student);

		int my_nigga = this->students.size() - 1; // latest inserted student

		while (my_nigga != 0 && students[my_nigga] > students[Student::get_parent(my_nigga)])
		{
			cout << "swapping " << my_nigga << " with " << Student::get_parent(my_nigga) << endl;
			swap(students[my_nigga], students[Student::get_parent(my_nigga)]);
			my_nigga = Student::get_parent(my_nigga);
		}

		return true;
	}

	void levelOrder() const
	{
		for (int i = 0; i < this->students.size(); i++)
		{
			cout << this->students[i].roll_num << ':' << this->students[i].cgpa << ' ';

			//if (i + 1 <= 2 << i)
			{

			}
		}

	}

	bool is_empty()
	{
		return this->students.empty();
	}

	bool is_full()
	{
		return false;
	}
};

int main(void)
{
	Student_MaxHeap std_mx_hp;

	std_mx_hp.insert(Student(1, 3.5));
	std_mx_hp.insert(Student(2, 2.7));
	std_mx_hp.insert(Student(4, 3.2));
	std_mx_hp.insert(Student(7, 3.9));

	std_mx_hp.levelOrder();

	return 0;
}