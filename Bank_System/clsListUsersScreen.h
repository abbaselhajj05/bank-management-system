#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

class clsListUsersScreen : protected clsScreen {
private:
	static void _printUserRecordLine(clsUser user) {
		cout << setw(4) << "" << "| " << left << setw(12) << user.userName;
		cout << "| " << left << setw(20) << user.fullName();
		cout << "| " << left << setw(20) << user.phone;
		cout << "| " << left << setw(20) << user.email;
		cout << "| " << left << setw(18) << user.password;
		cout << "| " << left << setw(12) << to_string(user.permissions) << endl;
	}

public:
	static void showListUsersScreen() {
		vector<clsUser> vUsers = clsUser::getUsersList();

		_drawScreenHeader("Users List Screen", "  (" + to_string(vUsers.size()) + ") Users(s).");
		cout << "\n" << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
		cout << setw(4) << "" << "| " << left << setw(12) << "User Name";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(20) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(18) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << "\n" << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";

		if (vUsers.size() == 0)
			cout << setw(48) << "" << "No users available in the system\n";
		else
			for (clsUser& user : vUsers)
				_printUserRecordLine(user);
		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
	}
};

