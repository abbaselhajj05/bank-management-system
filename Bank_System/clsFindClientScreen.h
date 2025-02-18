#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen {
private:
	static void _printClient(clsBankClient& client) {
		cout << "\nClient Card:";
		cout << "\n----------------------------------------";
		cout << "\nFirst name     : " << client.firstName;
		cout << "\nLast name      : " << client.lastName;
		cout << "\nFull name      : " << client.fullName();
		cout << "\nEmail          : " << client.email;
		cout << "\nPhone          : " << client.phone;
		cout << "\nAccount Number : " << client.accountNumber();
		cout << "\nPassword       : " << client.pinCode;
		cout << "\nBalance        : " << client.accountBalance;
		cout << "\n----------------------------------------\n";
	}

public:
	static void showFindClientScreen() {
		if (!clsScreen::checkAccessRights(clsUser::pFindClient))
			return;

		_drawScreenHeader("Find Client Screen");

		string accountNumber;
		cout << "Please enter client account number: ";
		accountNumber = clsInputValidate::readString();

		clsBankClient* client = clsBankClient::find(accountNumber);

		while (!client) {
			cout << "\nERROR! Account number not found!\nPlease enter a valid account number: ";
			accountNumber = clsInputValidate::readString();
			client = clsBankClient::find(accountNumber);
		}

		_printClient(*client);

		delete client;
		client = nullptr;
	}
};

