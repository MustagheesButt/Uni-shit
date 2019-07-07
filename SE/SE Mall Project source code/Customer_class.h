#pragma once
#ifndef CUSTOMER_CLASS_H
#define CUSTOMER_CLASS_H

#include <string>
#include <vector>

class Item {
public:
	Item(std::string name, double price, unsigned int store_id);

	unsigned int get_id() const;
	std::string get_name() const;
	double get_price() const;
	static Item get_item_by_id(std::vector<Item> items, unsigned int id);

private:
	static unsigned int item_counter;
	unsigned int id;
	std::string name;
	double price;
	unsigned int store_id;
};

class ShoppingCart
{
public:
	std::vector<Item> get_items() const;
	void push_item(const Item& item);
	void discard_item(const Item& item);
private:
	std::vector<Item> items;
};

class Customer
{
public:
	Customer();
	Customer(unsigned int id, std::string name, unsigned int store_id = NULL);

	unsigned int get_id() const;
	std::string get_name() const;
	unsigned int get_store_id() const;
	ShoppingCart get_cart() const;

	static Customer get_customer_by_id(const std::vector<Customer>& customers, unsigned int id);

	void set_name(std::string name);
	void set_store_id(unsigned int id);

	void push_in_cart(Item item);
	void discard_from_cart(const Item& item);
	
	bool operator== (Customer customer);

private:
	unsigned int id;
	std::string name;

	unsigned int store_id;
	ShoppingCart cart;
};

#endif // !CUSTOMER_CLASS_H