#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h";
using namespace std;

class clsAddNewUserScreen : public clsScreen {
private:
	static int _readPermissionsToSet() {
		cout << "\nDo you want to give full access [Y/N] ? ";
		char giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			return -1;

		int permittedOptions = 0;

		cout << "\nDo you want to give access to?\n";

		cout << setw(32) << right << "Show CLient List [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pShowClientList;

		cout << setw(32) << right << "Add New CLient [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pAddClient;

		cout << setw(32) << right << "Delete CLient [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pDeleteClient;

		cout << setw(32) << right << "Update CLient Info [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pUpdateClient;

		cout << setw(32) << right << "Find Client [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pFindClient;

		cout << setw(32) << right << "Transactions [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pTransactionsMenu;

		cout << setw(32) << right << "Manage Users [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pManageUsersMenu;

		cout << setw(32) << right << "Login Register [Y/N] => ";
		giveAccess = clsInputValidate::readChar();
		if (toupper(giveAccess) == 'Y')
			permittedOptions |= clsUser::enPermissions::pLoginRegister;

		return permittedOptions;
	}

	static void _readUserInfo(clsUser& user) {
		cout << "\nEnter First Name: ";
		user.firstName = clsInputValidate::readString();

		cout << "Enter Last Name: ";
		user.lastName = clsInputValidate::readString();

		cout << "Enter Email: ";
		user.email = clsInputValidate::readString();

		cout << "Enter Phone: ";
		user.phone = clsInputValidate::readString();

		cout << "Enter Password: ";
		user.password = clsInputValidate::readString();

		user.permissions = _readPermissionsToSet();
	}

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
	static void showAddNewUserScreen() {
		_drawScreenHeader("Add New User Screen");

		cout << "Please enter username: ";
		string userName = clsInputValidate::readString();

		while (clsUser::userExists(userName)) {
			cout << "\nUsername is already taken.\nPlease enter another one: ";
			userName = clsInputValidate::readString();
		}

		clsUser newUser = clsUser::createWithUserName(userName);
		_readUserInfo(newUser);
		
		newUser.add();
		cout << "\nUser Added Successfully\n";
		_printUser(newUser);
	}
};

