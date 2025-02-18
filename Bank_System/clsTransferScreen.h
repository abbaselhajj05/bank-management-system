#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen {
private:
	static clsBankClient* _readClient(string message) {
		string accountNumber;
		cout << message;
		accountNumber = clsInputValidate::readString();

		clsBankClient* client = clsBankClient::find(accountNumber);

		while (!client) {
			cout << "\nERROR! Account number not found!\nPlease enter a valid account number: ";
			accountNumber = clsInputValidate::readString();
			client = clsBankClient::find(accountNumber);
		}

		return client;
	}

	static void _printClient(clsBankClient& client) {
		cout << "\nClient Card:";
		cout << "\n----------------------------------------";
		cout << "\nFull name      : " << client.fullName();
		cout << "\nAccount Number : " << client.accountNumber();
		cout << "\nBalance        : " << client.accountBalance;
		cout << "\n----------------------------------------\n";
	}

public:
	static void showTransferScreen() {
		_drawScreenHeader("Transfer Screen");

		clsBankClient* senderClient = _readClient("Please enter Account number to transfer from: ");
		_printClient(*senderClient);

		clsBankClient* receiverClient;
		while (true) {
			receiverClient = _readClient("Please enter Account number to transfer to: ");
			if (receiverClient->accountNumber() != senderClient->accountNumber())
				break;
			cout << "\nERROR! Can't transfer to sender account.\n";
		}
		 
		_printClient(*receiverClient);

		cout << "Enter transfer amount: ";
		double amount = clsInputValidate::readPositiveDblNumber();

		while (amount > senderClient->accountBalance) {
			cout << "\nAmount exceeds the available balance!\nEnter another amount: ";
			amount = clsInputValidate::readPositiveDblNumber();
		}

		cout << "\nAre you sure you want to perform this operation [Y/N]? ";
		char confirmTransfer = clsInputValidate::readChar();
		if (!(toupper(confirmTransfer) == 'Y'))
			return;

		senderClient->transfer(amount, *receiverClient, currentUser->userName);

		cout << "\nTranfer was done successfully\n";

		_printClient(*senderClient);
		_printClient(*receiverClient);

		delete senderClient, receiverClient;
		senderClient = receiverClient = nullptr;

	}

};

