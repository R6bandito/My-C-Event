#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>

class Account {	//Bank account category

public:
	std::string name;	//Card holder's name
	std::string password;	//password
	uint64_t id;		//ID Num
	double balance;		
	std::stack<std::string> logs;	//History of transactions

	Account& operator=(const Account&) = delete; //Prohibit copy

public:
	Account():name(""),password(""),id(0),balance(0.0){}	//initialize

	virtual ~Account() {}	//Virtual destructuring to prevent the class from being used to instantiate objects

};

#endif // ACCOUNT_HPP

