#pragma once
#include <iostream>
#include <string>
#include "clsUtil.h";
#include "clsScreen.h";
#include "clsBankClient.h";
using namespace std;

class clsTotalBalancesScreen : protected clsScreen {
private:
	static void _printClientRecordBalanceLine(clsBankClient client) {
		cout << setw(36) << "" << "| " << left << setw(15) << client.accountNumber();
		cout << "| " << left << setw(30) << client.fullName();
		cout << "| " << left << setw(15) << client.accountBalance << endl;
	}

public:
	static void showTotalBalances() {
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string title = "Balances List Screen";
		string subtitle = "(" + to_string(vClients.size()) + ") Client(s)";
		_drawScreenHeader(title, subtitle);

		cout << "\n" << setw(32) << "" << "------------------------------------------------------------------\n";
		cout << setw(36) << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(15) << "Balance";
		cout << "\n" << setw(32) << "" << "------------------------------------------------------------------\n";

		double totalBalances = clsBankClient::getTotalBalances();

		if (vClients.size() == 0)
			cout << setw(48) << "" << "No clients available in the system\n";
		else
			for (clsBankClient& client : vClients)
				_printClientRecordBalanceLine(client);

		cout << setw(32) << "" << "------------------------------------------------------------------\n";
		cout << setw(32) << "" << "Total Balances = " << totalBalances << endl;
		cout << setw(32) << "" << "(" << ((totalBalances == 0) ? "Zero" : clsUtil::numberToText(totalBalances) + "\b") << ")\n";
	}

};

