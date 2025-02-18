#pragma once
#include <iostream>
#include "clsScreen.h";

using namespace std;
class clsClientListScreen : protected clsScreen {
private:
	static void _printClientRecordLine(clsBankClient client) {
		cout << "\t| " << left << setw(16) << client.accountNumber();
		cout << "| " << left << setw(20) << client.fullName();
		cout << "| " << left << setw(20) << client.phone;
		cout << "| " << left << setw(20) << client.email;
		cout << "| " << left << setw(10) << client.pinCode;
		cout << "| " << left << setw(8) << client.accountBalance << endl;
	}

public:
	static void showClientsList() {
		if (!clsScreen::checkAccessRights(clsUser::pShowClientList))
			return;

		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		_drawScreenHeader("Client List Screen","  (" + to_string(vClients.size()) + ") Client(s).");
		cout << "\n\t----------------------------------------------------------------------------------------------------------\n";
		cout << "\t| " << left << setw(16) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(20) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(8) << "Balance";
		cout << "\n\t----------------------------------------------------------------------------------------------------------\n";

		if (vClients.size() == 0)
			cout << setw(48) << "" << "No clients available in the system\n";
		else
			for (clsBankClient& client : vClients)
				_printClientRecordLine(client);
		cout << "\t----------------------------------------------------------------------------------------------------------\n";

	}
};

