#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"
using namespace std;

class clsScreen {
protected:
	static void _drawScreenHeader(string title, string subtitle = "") {
		cout << setw(40) << "" << "--------------------------------------------------\n";
		cout << setw(56) << "" << title;
		if (subtitle != "")
			cout << "\n" << setw(56) << "" << subtitle;
		cout << "\n" << setw(40) << "" << "--------------------------------------------------\n";

		string user;
		user = (currentUser == nullptr) ? "" : currentUser->userName;
		cout << "\n" << setw(56) << "" << "User: " << user;
		cout << "\n" << setw(56) << "" << "Date: " << clsDate::getFormattedDate(clsDate()) << "\n\n";
	}

	static bool checkAccessRights(clsUser::enPermissions permissions) {
		if (currentUser->checkAccessPermission(permissions))
			return true;

		cout << setw(40) << "" << "--------------------------------------------------\n";
		cout << setw(56) << "" << "Access Denied!";
		cout << "\n" << setw(48) << "" << "Contact your Admin for more info";
		cout << "\n" << setw(40) << "" << "--------------------------------------------------\n\n";
		return false;
	}
};

