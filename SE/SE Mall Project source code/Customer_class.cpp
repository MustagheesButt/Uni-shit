#include "Customer_class.h"
#include <iostream>

/* Item */
Item::Item(std::string name, double price, unsigned int store_id)
{
	this->id = this->item_counter;
	this->item_counter++;

	this->name = name;
	this->price = price;
	this->store_id = store_id;
}

unsigned int Item::get_id() const
{
	return this->id;
}

std::string Item::get_name() const
{
	return this->name;
}

double Item::get_price() const
{
	return this->price;
}

Item Item::get_item_by_id(std::vector<Item> items, unsigned int id)
{
	for (auto i : items)
	{
		//std::cout << i.get_id() << ' ' << id << '\n';
		if (i.get_id() == id)
			return i;
	}

	throw std::invalid_argument("ID not found while searching for items!.");
}

unsigned int Item::item_counter = 1;

/* ShoppingCart */
std::vector<Item> ShoppingCart::get_items() const
{
	return this->items;
}
void ShoppingCart::push_item(const Item& item)
{
	this->items.push_back(item);
}

void ShoppingCart::discard_item(const Item& item)
{
	for (int i = 0; i < this->get_items().size(); i++)
		if (this->get_items()[i].get_id() == item.get_id())
			this->items.erase(this->items.begin() + i);
}

/* Customer */
Customer::Customer()
{
	this->id = NULL;
	this->name = "";
	this->store_id = NULL;
}
Customer::Customer(unsigned int id, std::string name, unsigned int store_id)
{
	this->id = id;
	this->name = name;

	this->store_id = store_id;
}

unsigned int Customer::get_id() const
{
	return this->id;
}

std::string Customer::get_name() const
{
	return this->name;
}

unsigned int Customer::get_store_id() const
{
	return this->store_id;
}

ShoppingCart Customer::get_cart() const
{
	return this->cart;
}

Customer Customer::get_customer_by_id(const std::vector<Customer>& customers, unsigned int id)
{
	for (auto i : customers)
		if (i.get_id() == id)
			return i;

	throw std::invalid_argument("ID not found while searching for customers!");
}

void Customer::set_name(std::string name)
{
	this->name = name;
}

void Customer::set_store_id(unsigned int store_id)
{
	this->store_id = store_id;
}

void Customer::push_in_cart(Item item)
{
	this->cart.push_item(item);
}

void Customer::discard_from_cart(const Item& item)
{
	this->cart.discard_item(item);
}

bool Customer::operator== (Customer customer)
{
	return this->get_id() == customer.get_id() && this->get_name() == customer.get_name();
}