#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsListUsersScreen.h";
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h";
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";
using namespace std;

class clsManageUsersScreen : protected clsScreen {
private:
	enum enManageUsersMenuOption { ListUsers = 1, AddNewUser, DeleteUser, UpdateUser, FindUser, MainMenu };

	static short _readManageUsersMenuOption() {
		cout << setw(40) << "" << "Choose what do you want to do [1~6]? ";
		short choice = clsInputValidate::readShortNumberBetween(1, 6, "Enter a number between 1 and 6: ");
		return choice;
	} 

	static void _goBackToManageUsersMenu() {
		cout << "\n" << setw(40) << "" << "Press any key to go back to Manage Users Menu . . . ";
		system("pause > 0");
		showManageUsersMenu();
	}

	static void _showListUsersScreen() {
		clsListUsersScreen::showListUsersScreen();
	}

	static void _showAddNewUserScreen() {
		clsAddNewUserScreen::showAddNewUserScreen();
	}

	static void _showDeleteUserScreen() {
		clsDeleteUserScreen::_showDeleteUserScreen();
	}

	static void _showUpdateUserScreen() {
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _showFindUserScreen() {
		clsFindUserScreen::showFindUserScreen();
	}

	static void _performManageUsersMenuOption(enManageUsersMenuOption manageUsersMenuOption) {
		system("cls");

		switch (manageUsersMenuOption) {
		case enManageUsersMenuOption::ListUsers:
			_showListUsersScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOption::AddNewUser:
			_showAddNewUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOption::DeleteUser:
			_showDeleteUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOption::UpdateUser:
			_showUpdateUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOption::FindUser:
			_showFindUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOption::MainMenu:
			break;
		}
	}

public:
	static void showManageUsersMenu() {
		if (!clsScreen::checkAccessRights(clsUser::pManageUsersMenu))
			return;

		system("cls");
		_drawScreenHeader("Manage Users Screen");

		cout << setw(40) << "" << "==================================================\n";
		cout << setw(56) << "" << "Manage Users Menu\n";
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(48) << "" << "[1] List Users.\n";
		cout << setw(48) << "" << "[2] Add New User.\n";
		cout << setw(48) << "" << "[3] Delete User.\n";
		cout << setw(48) << "" << "[4] Update User Info.\n";
		cout << setw(48) << "" << "[5] Find User.\n";
		cout << setw(48) << "" << "[6] Main Menu.\n";
		cout << setw(40) << "" << "==================================================\n";

		_performManageUsersMenuOption((enManageUsersMenuOption)_readManageUsersMenuOption());

	}
};

