#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen {
private:
	static void _printLoginRegisterRecordLine(clsUser::stLoginRegisterRecord& record) {
		cout << setw(20) << "" << "| " << left << setw(16) << record.date;
		cout << "| " << left << setw(16) << record.time;
		cout << "| " << left << setw(16) << record.userName;
		cout << "| " << left << setw(16) << record.password;
		cout << "| " << left << setw(16) << record.permissions << endl;
	}

public:
	static void showLoginRegisterScreen() {
		if (!clsScreen::checkAccessRights(clsUser::pLoginRegister))
			return;

		vector<clsUser::stLoginRegisterRecord> vRecords = clsUser::getLoginRegisterList();

		_drawScreenHeader("Login Register List Screen", "  (" + to_string(vRecords.size()) + ") Users(s).");
		cout << "\n" << setw(20) << "" << "-----------------------------------------------------------------------------------------";
		cout << "\n" << setw(20) << "" << "| " << left << setw(16) << "Date";
		cout << "| " << left << setw(16) << "Time";
		cout << "| " << left << setw(16) << "Username";
		cout << "| " << left << setw(16) << "Password";
		cout << "| " << left << setw(16) << "Permissions";
		cout << "\n" << setw(20) << "" << "-----------------------------------------------------------------------------------------\n";

		for (clsUser::stLoginRegisterRecord& record : vRecords)
			_printLoginRegisterRecordLine(record);

		cout << setw(20) << "" << "-----------------------------------------------------------------------------------------\n";
	}
};

 