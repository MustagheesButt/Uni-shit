#pragma once
#include <string>

const std::string CUSTOMERS_DB = "DB/customers.db";
const std::string STORES_DB = "DB/stores.db";

const int EXIT_MAIN_LOOP = -1;

const int MAX_NAME_LENGTH = 40;

/** HELPERS **/

template<class T>
void cin_s(T& input)
{
	cin >> input; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
}