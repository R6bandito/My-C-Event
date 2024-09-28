#ifndef ATM_HPP
#define ATM_HPP

#define _CRT_SECURE_NO_WARNINGS

#include "Account.hpp"

using namespace std;

#define DEPOSIT 1
#define WITHDRAW 2
#define TRANSFER 3

double getAmount();
void Logs(size_t Mode, double amount, Account& account);
string getSystemTime();

class ATM {

private:
	Account account;
	vector<Account> accountsArr;	

	ATM(const ATM&) = delete;	//Prohibit copy

	ATM& operator=(const ATM&) = delete;	//Prohibit copy

public:
	ATM() :account(),accountsArr() {
		this->accountsArr.reserve(10);
	}	//initialize

	void InitAccounts();

	void Deposit();	

	void Withdraw();

	void ChangePassword();

	bool LogIn();
	
};

void ATM::InitAccounts() {	//This Function Can Be Executed Only Once
	cout << R"delimiter(							Welcome to our ATM!	
this is your first time here!,please create an account to continue.)delimiter" << endl << endl;

	cout << "Name:";
	getline(cin, this->account.name);
	cout << "ID:";
	while (true) {
		while (!(cin >> this->account.id)) {
			cout << "Wrong Input.Please Try Again!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if ((this->account.id > 0xE8D4A50FFF) || (this->account.id < 0x19DEBD01C7)) {	//The ID Num should have 12 bits
			cout << "Wrong Input.Please Try Again!" << endl;
			continue;
		}
		break;
	}
	cout << "Password:";
	while (true) {
		getline(cin, this->account.password);
		if ((this->account.password.length() > 20) || (this->account.password.length() < 6)) {	//The Password's length should be between 6 and 20
			cout << "Wrong Input.Please Try Again! The Password's length should be between 6 and 20" << endl;
			continue;
		}
		break;
	}

	this->accountsArr.push_back(this->account);
}

void ATM::Deposit() {
	double amount;
	cout<<"Please Enter The Amount You Want To Deposit:"<<endl;
	amount = getAmount();
	this->account.balance += amount;
	Logs(DEPOSIT,amount,this->account);
	cout<<"Deposit Success!"<<endl;
}

void ATM::Withdraw() {
	double amount;
	cout << "Please Enter how much you want to withdraw:" << endl;
	amount = getAmount();
	this->account.balance -= amount;
	Logs(WITHDRAW, amount, this->account);
	cout << "Withdraw Success!" << endl;
}

void ATM::ChangePassword() {
	string newPassword;
	cout << "Please Enter Your New Password:";
	getline(cin, newPassword);
	if (newPassword.length() > 20 || newPassword.length() < 6) {
		cout << "Wrong Input.Please Try Again! The Password's length should be between 6 and 20" << endl;
		return;
	}
	else if (newPassword == this->account.password) {
		cout << "Wrong!The Password You Enter Is The Same As The Old Password!" << endl;
		return;
	}
	this->account.password = newPassword;
	cout << "Successfully Changed!" << endl;
}

bool ATM::LogIn() {
	string password; uint64_t ID_num;
	cout << "Please Enter Your ID Number:";
	while (true) {
		while (!(cin >> ID_num)) {
			cout << "Wrong Input.Please Try Again!" << endl;
			cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if ((ID_num > 0xE8D4A50FFF) || (ID_num < 0x19DEBD01C7)) {	//The ID Num should have 12 bits
			cout << "Wrong Input.Please Try Again!" << endl;
			continue;
		}
		break;
	}
	cout << "Please Enter Your Password:";
	getline(cin, password);
	if ((password.length() > 20) || (password.length() < 6)) {	//The Password's length should be between 6 and 20
		cout << "Wrong Input.Please Try Again! The Password's length should be between 6 and 20" << endl;
		return false;
	}

	auto it = find_if(this->accountsArr.begin(), this->accountsArr.end(), [this, &password, &ID_num](const Account& account) {
	return (account.password == password) && (account.id == ID_num);
		});
	if (it != this->accountsArr.end()) {
		//Login Success
		return true;
	}
	else {
		//Login Failed
		return false;
	}
}


		

string getSystemTime() {	//Get Current Time
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	stringstream ss;
	ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
	return ss.str();
}

double getAmount() {	
	double amount;
	while (!(cin >> amount)) {
		cout << "Wrong Input,Please Try Again!" << endl;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return amount;
}

void Logs(size_t Mode,double amount,Account& account) {
	string msg;
	if (Mode == DEPOSIT) {
		msg = "Time:" + getSystemTime() + "   Deposit:" + to_string(amount) + "   AccountBalance:" + to_string(account.balance);
		account.logs.push(msg);
	}
	if (Mode == WITHDRAW) {
		msg = "Time:" + getSystemTime() + "   Withdraw:" + to_string(amount) + "   AccountBalance:" + to_string(account.balance);
		account.logs.push(msg);
	}
	if (Mode == TRANSFER) {
		msg = "Time:" + getSystemTime() + "   Transfer:" + to_string(amount) + "   AccountBalance:" + to_string(account.balance);
		account.logs.push(msg);
	}

}

#endif // ATM_HPP


