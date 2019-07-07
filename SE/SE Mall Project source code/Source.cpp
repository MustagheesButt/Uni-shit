#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "constants.h"
#include "Customer_class.h"
#include "Customer_Model.h"

using namespace std;

class Store
{
public:
	Store(string name)
	{
		this->name = name;

		this->id = this->store_counter;
		this->store_counter++;
	}

	virtual void enter(Customer& customer) = 0;
	virtual void exit(const Customer& customer) = 0;

	int main_menu()
	{
		int input;
		do
		{
			system("CLS");
			cout << "Welcome to " + this->name + ". Have a good time!\n";
			cout << "You can do the following here (1 - 4):\n"
				<< "1. Purchase an item.\n"
				<< "2. Discard items from shopping cart.\n"
				<< "3. List all customers in this store.\n"
				<< "4. Exit.\n";
			cin_s<int>(input);
		}
		while (input < 1 || input > 4);

		if (input == 1)
		{
			this->items_menu();
		}
		else if (input == 2)
		{
			this->discard_items_menu();
		}
		else if (input == 3)
		{
			this->print_customers();
		}
		else
		{
			this->exit(*this->curr_customer);
			return -1;
		}

		return 0;
	}

	void items_menu()
	{
		int input;
		do
		{
			system("CLS");
			cout << "Enter one of these items (1 - " << this->items.size() + 1 << "):\n";
			for (int i = 0; i < this->items.size(); i++)
				cout << i + 1 << ". " << this->items[i].get_name() << "\t\t" << this->items[i].get_price() << " USD\n";
			cout << this->items.size() + 1 << ". Back to main menu.\n";

			cin_s<int>(input);
		}
		while (input < 1 || input > this->items.size() + 1);

		if (input == this->items.size() + 1) // main menu
		{
			return;
		}
		else
		{
			this->curr_customer->push_in_cart(this->items[input - 1]);
		}
	}

	void discard_items_menu()
	{
		int input;
		do
		{
			system("CLS");
			cout << "Enter one of these items to discard (1 - " << this->curr_customer->get_cart().get_items().size() + 1 << "):\n";
			for (int i = 0; i < this->curr_customer->get_cart().get_items().size(); i++)
				cout << i + 1 << ". " << this->curr_customer->get_cart().get_items()[i].get_name() << ".\n";
			cout << this->curr_customer->get_cart().get_items().size() + 1 << ". Back to main menu.\n";

			cin_s<int>(input);
		} while (input < 1 || input > this->curr_customer->get_cart().get_items().size() + 1);

		if (input == this->curr_customer->get_cart().get_items().size() + 1) // main menu
		{
			return;
		}
		else
		{
			this->curr_customer->discard_from_cart(this->curr_customer->get_cart().get_items()[input - 1]);
		}
	}

	unsigned int get_store_id() const
	{
		return this->id;
	}

	string get_store_name() const
	{
		return this->name;
	}

	void push_item(Item item)
	{
		this->items.push_back(item);
	}

	void update_customers_index()
	{
		this->customers.clear();
		customer_model.read_all(this->customers, this->id);
	}

	void print_customers()
	{
		this->update_customers_index();

		cout << "Customers currently in " << this->get_store_name() << ":\n";
		for (auto i : this->customers)
			cout << i.get_id() << ' '
				<< i.get_name() << '\n';

		system("PAUSE");
	}

	static Store* get_store_by_id(vector<Store*> stores, unsigned int id)
	{
		for (auto i : stores)
			if (i->get_store_id() == id)
				return i;

		return NULL;
	}

private:
	static unsigned int store_counter;
	string name;
	unsigned int id;

	vector<Item> items;
	vector<Customer> customers;
	Customer* curr_customer;

	Customer_Model customer_model;
};

unsigned int Store::store_counter = 1;

void Store::enter(Customer& customer)
{
	this->update_customers_index();

	this->customers.push_back(customer);
	this->curr_customer = &customer;

	while (this->main_menu() != -1) {};
}

void Store::exit(const Customer& customer)
{
	this->curr_customer->set_store_id(NULL);
	this->customer_model.update(*this->curr_customer);

	this->customers.erase(std::remove(this->customers.begin(), this->customers.end(), customer), this->customers.end());
	//cout << "Goodbye " + customer.get_name() + "!\n";
	//system("PAUSE");
}

class BookStore : public Store
{
public:
	BookStore(string name) : Store(name)
	{}

	void enter(Customer& customer)
	{
		Store::enter(customer);
	}

	void exit(const Customer& customer)
	{
		Store::exit(customer);
	}
};

class GameStore : public Store
{
public:
	GameStore(string name) : Store(name)
	{}

	void enter(Customer& customer)
	{
		Store::enter(customer);
	}

	void exit(const Customer& customer)
	{
		Store::exit(customer);
	}
};

class ShoeStore : public Store
{
public:
	ShoeStore(string name) : Store(name)
	{}

	void enter(Customer& customer)
	{
		Store::enter(customer);
	}

	void exit(const Customer& customer)
	{
		Store::exit(customer);
	}
};

class Mall
{
public:
	Mall(string name)
	{
		this->name = name;

		ifstream stores_db(STORES_DB);
	
		/* reading in stores */
		while (true)
		{
			Store* new_store;
			string store_name, store_type;
			int n_items;

			getline(stores_db, store_name);

			if (stores_db.eof())
				break;

			getline(stores_db, store_type);

			if (store_type == "book_store")
			{
				new_store = new BookStore(store_name);
			}
			else if (store_type == "game_store")
			{
				new_store = new GameStore(store_name);
			}
			else
			{
				new_store = new ShoeStore(store_name);
			}

			stores_db >> n_items; stores_db.ignore();

			// read in items
			for (int i = 0; i < n_items; i++)
			{
				string item_name;
				double item_price;

				getline(stores_db, item_name);
				stores_db >> item_price; stores_db.ignore();

				Item new_item(item_name, item_price, new_store->get_store_id());

				new_store->push_item(new_item);
				this->items.push_back(new_item);
			}

			this->stores.push_back(new_store);
		}

		stores_db.close();

		/* read in customers */
		this->update_customers_index();
	}

	string get_name() const
	{
		return this->name;
	}

	void enter(string customer_name)
	{
		this->update_customers_index();

		// new id = LAST_INSERT Customer ID 
		Customer* new_customer;
		if (this->customers.size() > 0)
			new_customer = new Customer(this->customers[this->customers.size() - 1].get_id() + 1, customer_name);
		else
			new_customer = new Customer(1, customer_name);
		
		customer_model.insert(*new_customer);

		this->customers.push_back(*new_customer);
		this->curr_customer = *new_customer;

		delete new_customer;
	}

	void exit(Customer customer)
	{
		this->customer_model.remove(customer);
		this->customers.erase(std::remove(this->customers.begin(), this->customers.end(), customer), this->customers.end());	

		cout << "Thank you for visiting!\n";
	}

	void checkout()
	{
		//Transactions_Model::insert(this->curr_customer, this->items);
		this->exit(this->curr_customer);
	}

	// entrance point into the main loop
	void start(string customer_name)
	{
		this->enter(customer_name);
		while (this->main_menu() != -1) {};
	}

	int main_menu()
	{
		int input;
		do
		{
			system("CLS");
			cout << "Welcome to " << this->get_name() << ", " << this->curr_customer.get_name() << "!\n";
			cout << "Here's what you can do (1 - 4):\n"
				<< "1. Enter a Store.\n"
				<< "2. Checkout.\n"
				<< "3. See all Customers.\n"
				<< "4. Exit.\n";

			cin_s<int>(input);
		}
		while (input < 1 || input > 4);

		if (input == 1)
		{
			this->stores_menu();
		}
		else if (input == 2)
		{
			return this->checkout_menu();
		}
		else if (input == 3)
		{
			this->print_customers();
		}
		else
		{
			this->exit(this->curr_customer);
			return EXIT_MAIN_LOOP;
		}

		return 0;
	}

	void stores_menu()
	{
		int input;
		do
		{
			system("CLS");
			cout << "Enter one of these stores (1 - " << this->stores.size() + 1 << "):\n";
			for (int i = 0; i < this->stores.size(); i++)
				cout << i + 1 << ". " << this->stores[i]->get_store_name() << ".\n";
			cout << this->stores.size() + 1 << ". Back to main menu.\n";

			cin_s<int>(input);
		}
		while (input < 1 || input > this->stores.size() + 1);

		if (input == this->stores.size() + 1) // main menu
		{
			return;
		}
		else
		{
			this->curr_customer.set_store_id(input);
			//cout << "before: " << this->curr_customer.get_id() << ' ';
			this->customer_model.update(this->curr_customer);
			this->update_customers_index();
			//cout << "after: " << this->curr_customer.get_id() << '\n';

			this->stores[input - 1]->enter(this->curr_customer);
		}
	}

	int checkout_menu()
	{
		char input;
		double total = 0;

		system("CLS");
		cout << "Here's your bill:\n";
		for (auto i : this->curr_customer.get_cart().get_items())
		{
			Item temp = i;
			cout << left << setw(30) << temp.get_name() << '\t' << temp.get_price() << " USD\n";

			total += temp.get_price();
		}
		cout << left << setw(30) << "Total:\t" << total << " USD\n";
		cout << "Do you want to proceed? (Y/N): ";
		cin_s<char>(input);

		if (input == 'Y' || input == 'y')
		{
			this->checkout();
			return EXIT_MAIN_LOOP;
		}

		return 0;
	}

	void update_customers_index()
	{
		this->customers.clear();
		customer_model.read_all(this->customers);
		//cout << "INDEX UPDATED SUCCESSFULLY!\n";
		if (this->curr_customer.get_id() != NULL)
		{
			Customer temp = this->curr_customer;
			this->curr_customer = Customer::get_customer_by_id(this->customers, this->curr_customer.get_id());
			
			// to keep cart items
			for (auto i : temp.get_cart().get_items())
				this->curr_customer.push_in_cart(i);
		}
	}

	void print_customers()
	{
		this->update_customers_index();

		Store* temp_store;

		cout << "Customers currently in the mall:\n";
		for (auto i : this->customers)
			cout << i.get_id() << ' '
				<< i.get_name() << " in "
				<< (((temp_store = Store::get_store_by_id(this->stores, i.get_store_id())) == NULL) ? "Mall" : temp_store->get_store_name()) << '\n';

		system("PAUSE");
	}

private:
	string name;
	vector<Store*> stores;
	vector<Item> items;
	vector<Customer> customers; // active customers
	Customer curr_customer;

	Customer_Model customer_model;
};

/*
 * Each instance of main is a new session.
 */
int main(void)
{
	Mall mega_mall("Mega Mall");

	string customer_name;

	cout << "Welcome to " << mega_mall.get_name() << "!\nEnter your name: ";
	getline(cin, customer_name);

	mega_mall.start(customer_name);

	system("PAUSE");
	return 0;
}