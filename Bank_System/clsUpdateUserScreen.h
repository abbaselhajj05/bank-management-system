#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen {
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
		user.password = clsUtil::encryptText(clsInputValidate::readString(), clsUser::key);

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
	static void showUpdateUserScreen() {
		_drawScreenHeader("Update User Screen");

		cout << "Please enter username: ";
		string userName = clsInputValidate::readString();
		
		clsUser* user = clsUser::find(userName);

		while (!user) {
			cout << "\nERROR! User not found!\nPlease enter a valid username: ";
			userName = clsInputValidate::readString();
			user = clsUser::find(userName);
		}

		_printUser(*user);

		cout << "Are you sure you want to update this client [Y/N]? ";
		char confirmUpdate = clsInputValidate::readChar();
		if (!(toupper(confirmUpdate) == 'Y'))
			return;

		cout << "\nUpdate User Info:";
		cout << "\n-------------------";

		_readUserInfo(*user);
		user->update();
		cout << "\nAccount Updated Successfully!\n";
		_printUser(*user);

		delete user;
		user = nullptr;
	}
};

