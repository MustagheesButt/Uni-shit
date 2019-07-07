#pragma once

#ifndef CUSTOMER_MODEL_H
#define CUSTOMER_MODEL_H

class Customer;
#include <vector>

class Customer_Model
{
public:
	void insert(const Customer& customer);
	void update(const Customer& customer);
	void read_all(std::vector<Customer>& fill_this, unsigned int store_id = NULL);
	void remove(const Customer& customer);
private:

};

#endif