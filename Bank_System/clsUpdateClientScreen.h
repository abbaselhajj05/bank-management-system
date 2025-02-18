#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
using namespace std;

class clsUpdateClientScreen : protected clsScreen {
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
	static void showUpdateClientScreen() {
		if (!clsScreen::checkAccessRights(clsUser::pUpdateClient))
			return;

		_drawScreenHeader("Update Client Screen");

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

		cout << "Are you sure you want to update this client [Y/N]? ";
		char confirmUpdate = clsInputValidate::readChar();
		if (!(toupper(confirmUpdate) == 'Y'))
			return;

		cout << "\nUpdate Client Info:";
		cout << "\n-------------------";

		_readClientInfo(*client);
		client->update();
		cout << "\nAccount Updated Successfully!\n";
		_printClient(*client);

		delete client;
		client = nullptr;
	}
};

