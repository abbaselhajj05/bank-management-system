#pragma once
#include "clsScreen.h"

class clsDeleteUserScreen : protected clsScreen {
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
	static void _showDeleteUserScreen() {
		_drawScreenHeader("Delete User Screen");

		string userName;
		cout << "Please enter username: ";
		userName = clsInputValidate::readString();

		clsUser* user = clsUser::find(userName);

		while (!user) {
			cout << "\nUser not found!\nPlease enter a valid username: ";
			userName = clsInputValidate::readString();
			user = clsUser::find(userName);
		}

		_printUser(*user);

		cout << "\nAre you sure you want to delete this user [Y/N]? ";
		char confirmDelete = clsInputValidate::readChar();
		if (!(toupper(confirmDelete) == 'Y'))
			return;

		user->Delete();
		cout << "\nUser Deleted Successfully!\n";

		delete user;
		user = nullptr;
	}
};

