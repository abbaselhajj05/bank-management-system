#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";
using namespace std;

class clsWithdrawScreen : protected clsScreen {
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
	static void showWithdrawScreen() {
		_drawScreenHeader("Withdraw Screen");

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

		cout << "\nPlease enter withdraw amount? ";
		double amount = clsInputValidate::readPositiveDblNumber();

		while (amount > client->accountBalance) {
			cout << "Amount Exceeds the balance, you can withdraw up to: " << client->accountBalance << ".\n";
			cout << "\nPlease enter another amount: ";
			amount = clsInputValidate::readPositiveDblNumber();
		}

		cout << "\nAre you sure you want to perform this transaction [Y/N]? ";
		char confirmWithdraw = clsInputValidate::readChar();
		if (!(toupper(confirmWithdraw) == 'Y')) {
			cout << "\nOperation was cancelled.\n";
			return;
		}

		client->withdraw(amount);
		cout << "\nAmount was withdrawn successfully!\n";
		cout << "New balance: " << client->accountBalance;

		delete client;
		client = nullptr;
	}

};

