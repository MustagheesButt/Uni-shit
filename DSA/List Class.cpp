#include <iostream>

using namespace std;

class List
{
private:
	int *base_ptr;
	int max_size;
	int curr_size;
	int cursor;

public:
	List(int size)
	{
		this->max_size = size;
		this->base_ptr = new int[size];
		this->curr_size = 0;
		this->cursor = -1;
	}

	~List()
	{
		delete[] this->base_ptr;
	}

	/* Util */
	void insert(int new_element)
	{
		if (this->curr_size == this->max_size)
		{
			cout << "Error: List is full. Cannot insert.\n";
			return;
		}

		this->base_ptr[this->cursor + 1] = new_element;
		this->curr_size++;
		this->cursor++;
	}

	void remove(void)
	{
		if (this->curr_size == 0)
		{
			cout << "Error: List is empty. Cannot remove.\n";
			return;
		}

		this->base_ptr[this->cursor] = this->base_ptr[this->curr_size - 1];
		this->curr_size--;

		if (this->cursor == this->curr_size && this->curr_size == 0)
			this->cursor = -1;
		else if (this->cursor == this->curr_size)
			this->cursor = 0;
		else
			this->cursor--;
	}

	void replace(int new_item)
	{
		if (this->cursor != -1)
			this->base_ptr[this->cursor] = new_item;
	}

	void clear()
	{
		this->curr_size = 0;
		this->cursor = -1;
	}

	bool is_empty(void) const
	{
		return this->curr_size == 0;
	}

	bool is_full(void) const
	{
		return this->curr_size == this->max_size;
	}

	void go_to_beginning()
	{
		if (this->curr_size > 0)
			this->cursor = 0;
	}

	void go_to_end()
	{
		if (this->curr_size > 0)
			this->cursor = this->curr_size - 1;
	}

	bool go_to_next()
	{
		if (this->cursor == this->max_size - 1)
			return false;

		this->cursor++;
		return true;
	}

	bool go_to_prev()
	{
		if (this->cursor <= 0)
			return false;

		this->cursor--;
		return true;
	}

	int get_at_cursor(void) const
	{
		if (this->curr_size == 0)
		{
			cout << "Error: Empty list. Nothing at cursor.\n";
			return -1;
		}

		return this->base_ptr[this->cursor];
	}

	void show_list(void) const
	{
		if (this->curr_size == 0)
		{
			cout << "Empty List :(\n";
			return;
		}

		for (int i = 0; i < this->curr_size; i++)
			cout << this->base_ptr[i] << '\n';
	}
};

int main(void)
{
	List my_list(5);
	my_list.show_list();

	my_list.insert(44);
	my_list.insert(55);
	my_list.insert(66);
	my_list.insert(77);
	my_list.insert(88);
	my_list.insert(99);
	
	my_list.show_list();
	cout << "removing " << my_list.get_at_cursor() << "...\n";
	my_list.remove();
	my_list.show_list();
	cout << "At cursor: " << my_list.get_at_cursor() << '\n';

	system("PAUSE");

	return 0;
}