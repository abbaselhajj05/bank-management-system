#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsFindUserScreen : protected clsScreen {
private:
	static void _printUser(clsUser& user) {
		cout << "\nClient Card:";
		cout << "\n----------------------------------------";
		cout << "\nFirst name     : " << user.firstName;
		cout << "\nLast name      : " << user.lastName;
		cout << "\nFull name      : " << user.fullName();
		cout << "\nEmail          : " << user.email;
		cout << "\nPhone          : " << user.phone;
		cout << "\nPassword       : " << user.password;
		cout << "\nPermissions    : " << user.permissions;
		cout << "\n----------------------------------------\n";
	}

public:
	static void showFindUserScreen() {
		_drawScreenHeader("Find User Screen");

		string userName;
		cout << "Please enter client account number: ";
		userName = clsInputValidate::readString();

		clsUser* user = clsUser::find(userName);

		while (!user) {
			cout << "\nERROR! User not found!\nPlease enter a valid username: ";
			userName = clsInputValidate::readString();
			user = clsUser::find(userName);
		}

		_printUser(*user);

		delete user;
		user = nullptr;
	}
};

