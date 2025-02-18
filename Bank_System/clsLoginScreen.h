#pragma once
#include <vector>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen {
private:

	static bool _login() {
		string userName, password; 
		bool validUser = true;
		short trials = 3;

		do {
			cout << "Enter Username: ";
			userName = clsInputValidate::readString();

			cout << "Enter Password: ";
			password = clsInputValidate::readString();

			currentUser = clsUser::find(userName, password);

			if (!(validUser = currentUser)) {
				cout << "\nInvalid Username/Password!";
				cout << "\nYou have " << --trials << " trial(s) to login.\n";
			}

		} while (!validUser && trials > 0);

		if (trials == 0 && !validUser) {
			cout << "\nYou are locked after 3 failed trials.\n";;
			return false;
		}

		currentUser->registerLogin();
		clsMainScreen::showMainMenu();
		return true;
	}

public:
	static bool showLoginScreen() {
		system("cls");
		_drawScreenHeader("Login Screen");
		return _login();
	}
};

