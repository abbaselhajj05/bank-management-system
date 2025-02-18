#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
using namespace std;

class clsAddNewClientScreen : protected clsScreen {
private:
	static void _readClientInfo(clsBankClient& client) {
		cout << "\nEnter First Name: ";
		client.firstName = clsInputValidate::readString();

		cout << "Enter Last Name: ";
		client.lastName = clsInputValidate::readString();

		cout << "Enter Email: ";
		client.email = clsInputValidate::readString();

		cout << "Enter Phone: ";
		client.phone = clsInputValidate::readString();

		cout << "Enter PinCode: ";
		client.pinCode = clsInputValidate::readString();

		cout << "Enter Account Balance: ";
		client.accountBalance = clsInputValidate::readFloatNumber();
	}

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
	static void showAddNewClientScreen() {
		if (!clsScreen::checkAccessRights(clsUser::pAddClient))
			return;

		_drawScreenHeader("Add New Client Screen");

		string accountNumber;
		cout << "Please enter an account number: ";
		accountNumber = clsInputValidate::readString();

		while (clsBankClient::clientExists(accountNumber)) {
			cout << "\nAccount number is already taken.\nPlease enter another one: ";
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient newClient = clsBankClient::createWithAccountNumber(accountNumber);
		_readClientInfo(newClient);

		newClient.add();
		cout << "\nAccount Added Successfully!\n";
		_printClient(newClient);
	}
};

