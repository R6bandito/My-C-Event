#include "ATM.hpp"
#include <iostream>

once_flag flag;

using namespace std;
int main(int argc, const char* argv[]) {
	ATM	atm;
	while (true) {
		call_once(flag, [&atm]() {
			atm.InitAccounts();
			});
		atm.Deposit();
	}
	return 0;
}