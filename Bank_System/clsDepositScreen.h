#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";
using namespace std;

class clsDepositScreen : protected clsScreen {
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
	static void showDepositScreen() {
		_drawScreenHeader("Deposit Screen");

		string accountNumber;
		cout << "Please enter an account number: ";
		accountNumber = clsInputValidate::readString();

		clsBankClient* client = clsBankClient::find(accountNumber);

		while (!client) {
			cout << "\nClient with account number [" << accountNumber << "] does not exist!";
			cout << "\nPlease enter a valid account number : ";
			accountNumber = clsInputValidate::readString();
			client = clsBankClient::find(accountNumber);
		}

		_printClient(*client);

		cout << "\nPlease enter deposit amount? ";
		double amount = clsInputValidate::readPositiveDblNumber();

		cout << "\nAre you sure you want to perform this transaction [Y/N]? ";
		char confirmDeposit = clsInputValidate::readChar();
		if (!(toupper(confirmDeposit) == 'Y')) {
			cout << "\nOperation was cancelled.\n";
			return;
		}

		client->deposit(amount);
		cout << "\nAmount was deposited successfully!\n";
		cout << "New balance: " << client->accountBalance;

		delete client;
		client = nullptr;
	}
};

