#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Book
{
	friend class BookList;
private:
	int id;
	string title;
	float price;

	Book* next;
	Book* prev;

public:
	Book(int id, string title, float price, Book* next, Book* prev)
	{
		this->id = id;
		this->title = title;
		this->price = price;
		
		this->next = next;
		this->prev = prev;
	}

	int get_id()
	{
		return this->id;
	}

	string get_title()
	{
		return this->title;
	}
};

class BookList
{
private:
	Book *head; //start of the list
	Book *cursor; //current item of the list
	Book* last;

public:
	BookList()
	{
		this->head = NULL;
		this->cursor = NULL;
		this->last = NULL;
	}

	~BookList()
	{
		Book* iterator = this->head;

		do
		{
			Book* temp = iterator;
			iterator = iterator->next;
			delete temp;
		} while (iterator != NULL);
	}

	void insert(const Book& std)
	{
		Book* temp = new Book(std);

		if (this->isEmpty())
		{
			this->head = temp;
			this->cursor = temp;
			this->last = temp;

			return;
		}

		if (this->cursor->next != NULL)
		{
			temp->next = this->cursor->next;
			temp->prev = this->cursor;

			this->cursor->next->prev = temp;
			
			this->cursor->next = temp;
			
			this->cursor = temp;
		}
		else
		{
			temp->prev = this->cursor;
			
			this->cursor->next = temp;
			
			this->cursor = temp;
			
			this->last = temp;
		}
	}

	void remove()
	{
		if (this->isEmpty())
		{
			cout << "Failed to remove.\n";
			return;
		}

		cout << "\nRemoving book at cursor: ID = " << this->cursor->get_id() << " Title = " << this->cursor->get_title() << '\n';

		if (this->cursor == this->head && this->cursor->next != NULL) // first but not one
		{
			this->head = this->cursor->next;

			delete this->cursor;

			this->cursor = this->head;
			this->head->prev = NULL;
		}
		else if (this->cursor == this->head && this->cursor->next == NULL) // first and last item
		{		
			this->head = NULL;
			this->last = NULL;

			delete this->cursor;

			this->cursor = NULL;
		}
		else if (this->cursor->next != NULL)
		{
			this->cursor->prev->next = this->cursor->next;
			this->cursor->next->prev = this->cursor->prev;
			
			Book* temp = this->cursor->next;

			delete this->cursor;

			this->cursor = temp;
		}
		else
		{
			this->cursor->prev->next = NULL;
			Book* temp = this->cursor->prev;

			delete this->cursor;

			this->cursor = temp;
		}

	}

	void search(string title) const
	{
		if (this->isEmpty())
		{
			cout << "List is empty!\n";
			return;
		}

		Book* iterator = this->head;
		
		do
		{
			if (iterator->title == title)
				cout << "ID: " << iterator->id << ", Name: " << iterator->title << ", Price: " << iterator->price << endl;

			iterator = iterator->next;
		}
		while (iterator != NULL);
	}

	void replace(const Book& newStd)
	{
		if (this->isEmpty())
		{
			this->insert(newStd);
			return;
		}

		this->cursor->id = newStd.id;
		this->cursor->title = newStd.title;
		this->cursor->price = newStd.price;
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
		this->cursor = this->last;
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

		if (this->cursor->prev != NULL)
		{
			this->cursor = this->cursor->prev;
			return true;
		}

		return false;
	}

	Book getCursor()
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

		Book* iterator = this->head;
		do
		{
			cout << "ID: " << iterator->id << ", Name: " << iterator->title << ", Price: " << iterator->price << endl;

			iterator = iterator->next;
		}
		while (iterator != NULL);
	}
};

int main(void)
{
	fstream in_file("input.txt");

	BookList my_list;

	while (true)
	{
		int id; string name; float price;

		in_file >> id; in_file.ignore();

		if (in_file.eof())
			break;

		getline(in_file, name);

		in_file >> price;

		Book book(id, name, price, NULL, NULL);

		my_list.insert(book);
	}

	my_list.show_structure();
	
	// removing
	my_list.remove();

	// removing
	my_list.gotoBeginning();
	my_list.remove();

	my_list.show_structure();


	// search
	string title;
	cout << "\nSearch for Book by Title: ";

	//cin.ignore();
	getline(cin, title);
	cout << "\nSearching for " << title << ":\n";
	my_list.search(title);

	in_file.close();

	return 0;
}
