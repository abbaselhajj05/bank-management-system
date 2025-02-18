#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
using namespace std;

class clsDeleteClientScreen : protected clsScreen {
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
	static void showDeleteClientScreen() {
		if (!clsScreen::checkAccessRights(clsUser::pDeleteClient))
			return;

		_drawScreenHeader("Delete Client Screen");

		string accountNumber;
		cout << "Please enter an account number: ";
		accountNumber = clsInputValidate::readString();

		clsBankClient* client = clsBankClient::find(accountNumber);

		while (!client) {
			cout << "\nAccount number not found!\nPlease enter a valid account number: ";
			accountNumber = clsInputValidate::readString();
			client = clsBankClient::find(accountNumber);
		}

		_printClient(*client);

		cout << "\nAre you sure you want to delete this client [Y/N]? ";
		char confirmDelete = clsInputValidate::readChar();
		if (!(toupper(confirmDelete) == 'Y'))
			return;

		if (client->Delete())
			cout << "\nAccount Deleted Successfully!\n";
		else
			cout << "\nERROR! User was not deleted.\n";

		delete client;
		client = nullptr;
	}
};