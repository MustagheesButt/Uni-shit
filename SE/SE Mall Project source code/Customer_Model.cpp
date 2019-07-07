#include "Customer_Model.h"

#include "constants.h"
#include <fstream>
#include "Customer_class.h"
#include <iostream>

void Customer_Model::insert(const Customer& customer)
{
	std::ofstream customers_db(CUSTOMERS_DB, std::ios::binary | std::ios::app);

	unsigned int id = customer.get_id();
	//std::string name = customer.get_name();
	char name[MAX_NAME_LENGTH];
	strcpy_s(name, customer.get_name().c_str());
	unsigned int store_id = customer.get_store_id();

	customers_db.write(reinterpret_cast<char*>(&id), sizeof(int));
	customers_db.write(reinterpret_cast<char*>(&name), sizeof(char) * MAX_NAME_LENGTH);
	customers_db.write(reinterpret_cast<char*>(&store_id), sizeof(int));

	customers_db.close();
}

void Customer_Model::update(const Customer& customer)
{
	unsigned int id = customer.get_id();
	char name[MAX_NAME_LENGTH]; strcpy_s(name, customer.get_name().c_str());
	unsigned int store_id = customer.get_store_id();

	unsigned int read_id = NULL;
	std::streamoff location;

	/* PROBING */
	std::ifstream customers_db(CUSTOMERS_DB, std::ios::binary);
	while (read_id != id && !customers_db.eof())
	{
		customers_db.read(reinterpret_cast<char*>(&read_id), sizeof(int));

		if (customers_db.eof() || read_id == id)
		{
			location = customers_db.tellg();
			break;
		}

		customers_db.seekg(sizeof(char) * MAX_NAME_LENGTH + sizeof(int), std::ios::cur);
	}

	customers_db.close();

	/* UPDATING */
	if (read_id == id)
	{
		std::ofstream customers_db2(CUSTOMERS_DB, std::ios::binary | std::ios::in | std::ios::out | std::ios::beg);
		
		customers_db2.seekp(location - 4, std::ios::beg);
		
		customers_db2.write(reinterpret_cast<char*>(&id), sizeof(int));
		customers_db2.write(reinterpret_cast<char*>(&name), sizeof(char) * MAX_NAME_LENGTH);
		customers_db2.write(reinterpret_cast<char*>(&store_id), sizeof(int));

		customers_db2.close();

		//std::cout << "\n Updated rid: " << read_id << " id: " << id << '\n';
	}
}

void Customer_Model::read_all(std::vector<Customer>& fill_this, unsigned int filter_store_id)
{
	std::ifstream customers_db(CUSTOMERS_DB, std::ios::binary);

	while (true)
	{
		unsigned int id;
		char name[MAX_NAME_LENGTH];
		unsigned int store_id;

		customers_db.read(reinterpret_cast<char*>(&id), sizeof(int));

		if (customers_db.eof())
			break;
		customers_db.read(reinterpret_cast<char*>(&name), sizeof(char) * MAX_NAME_LENGTH);
		customers_db.read(reinterpret_cast<char*>(&store_id), sizeof(int));
		//name[4] = '\0';
		if (filter_store_id == NULL || store_id == filter_store_id)
		{
			fill_this.push_back(Customer(id, name, store_id));
			//std::cout << "pushed " << id << ' ' << name << ' ' << store_id << '\n';
		}

		//std::cout << "reading " << name << ' ' << store_id << '\n';
	}

	customers_db.close();
}

void Customer_Model::remove(const Customer& customer)
{
	std::ofstream temp("temp.dat", std::ios::binary);
	std::ifstream customers_db(CUSTOMERS_DB, std::ios::binary);

	while (true)
	{
		unsigned int id;
		char name[MAX_NAME_LENGTH];
		unsigned int store_id;

		customers_db.read(reinterpret_cast<char*>(&id), sizeof(int));

		if (customers_db.eof())
			break;

		customers_db.read(reinterpret_cast<char*>(&name), sizeof(char) * MAX_NAME_LENGTH);
		customers_db.read(reinterpret_cast<char*>(&store_id), sizeof(int));

		if (customer.get_id() != id)
		{
			temp.write(reinterpret_cast<char*>(&id), sizeof(unsigned int));
			temp.write(reinterpret_cast<char*>(&name), sizeof(char)*40);
			temp.write(reinterpret_cast<char*>(&store_id), sizeof(unsigned int));
		}
	}

	customers_db.close();
	temp.close();
	std::remove(CUSTOMERS_DB.c_str());
	std::rename("temp.dat", CUSTOMERS_DB.c_str());
}