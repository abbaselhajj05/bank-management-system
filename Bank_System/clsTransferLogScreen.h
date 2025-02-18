#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen {
private:
	static void _printTransferLogRecordLine(clsBankClient::stTransferLogRecord& record) {
		cout << setw(16) << "" << "| " << left << setw(12) << record.date;
		cout << "| " << left << setw(10) << record.time;
		cout << "| " << left << setw(10) << record.senderAccountNumber;
		cout << "| " << left << setw(10) << record.receiverAccountNumber;
		cout << "| " << left << setw(12) << record.amount;
		cout << "| " << left << setw(12) << record.senderAccountBalanceAfter;
		cout << "| " << left << setw(12) << record.receiverAccountBalanceAfter;
		cout << "| " << left << setw(10) << record.userName << endl;
	}

public:
	static void showTransferLogScreen() {
		vector<clsBankClient::stTransferLogRecord> vRecords = clsBankClient::getTransferLogRecords();

		_drawScreenHeader("Transfer Log List Screen", "  (" + to_string(vRecords.size()) + ") Record(s).");

		cout << "\n" << setw(16) << "" << "----------------------------------------------------------------------------------------------------";
		cout << "\n" << setw(16) << "" << "| " << left << setw(12) << "Date";
		cout << "| " << left << setw(10) << "Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(12) << "Amount";
		cout << "| " << left << setw(12) << "s.Balance";
		cout << "| " << left << setw(12) << "d.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << "\n" << setw(16) << "" << "----------------------------------------------------------------------------------------------------\n";

		for (clsBankClient::stTransferLogRecord& record : vRecords)
			_printTransferLogRecordLine(record);
		cout << setw(16) << "" << "----------------------------------------------------------------------------------------------------\n";
	}
};

