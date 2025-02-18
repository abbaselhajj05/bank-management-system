#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsClientListScreen.h";
#include "clsAddNewClientScreen.h";
#include "clsDeleteClientScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionsScreen.h";
#include "clsManageUsersScreen.h";
#include "clsLoginRegisterScreen.h";
#include "clsCurrencyExchangeScreen.h";
#include "clsInputValidate.h";
#include "Global.h";
using namespace std;

class clsMainScreen : protected clsScreen {
private:
	enum enMainMenuOption { ShowClientList = 1, AddNewClient, DeleteClient, UpdateClient, FindClient, TransactionsMenu, ManageUsersMenu, LoginRegister, CurrencyExchange, Exit };

	static short _readMainMenuOption() {
		cout << setw(40) << "" << "Choose what do you want to do [1~10]? ";
		short choice = clsInputValidate::readShortNumberBetween(1, 10, "Enter a number between 1 and 10: ");
		return choice;
	}

	static void _goBackToMainMenu() {
		cout << "\n" << setw(40) << "" << "Press any key to go back to Main Menu . . . ";
		system("pause > 0");
		showMainMenu();
	}

	static void _showClientListScreen() {
		clsClientListScreen::showClientsList();
	}

	static void _showAddNewClientsScreen() {
		clsAddNewClientScreen::showAddNewClientScreen();
	}

	static void _showDeleteClientScreen() {
		clsDeleteClientScreen::showDeleteClientScreen();
	}

	static void _showUpdateClientScreen() {
		clsUpdateClientScreen::showUpdateClientScreen();
	}

	static void _showFindClientScreen() {
		clsFindClientScreen::showFindClientScreen();
	}

	static void _showTransactionsMenu() {
		clsTransactionsScreen::showTransactionsMenu();
	}

	static void _showManageUsersMenu() {
		clsManageUsersScreen::showManageUsersMenu();
	}

	static void _showLoginRegisterScreen() {
		clsLoginRegisterScreen::showLoginRegisterScreen();
	}

	static void _showCurrencyExchangeMenu() {
		clsCurrencyExchangeScreen::showCurrencyExchangeMenu();
	}

	static void _logout() {
		system("cls");
		currentUser = nullptr;
	}

	static void _performManageUsersMenuOption(enMainMenuOption mainMenuOption) {
		system("cls");
		switch (mainMenuOption) {
		case enMainMenuOption::ShowClientList:
			_showClientListScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::AddNewClient:
			_showAddNewClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::DeleteClient:
			_showDeleteClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::UpdateClient:
			_showUpdateClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::FindClient:
			_showFindClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::TransactionsMenu:
			_showTransactionsMenu();
			showMainMenu();
			break;
		case enMainMenuOption::ManageUsersMenu:
			_showManageUsersMenu();
			showMainMenu();
			break;
		case enMainMenuOption::LoginRegister:
			_showLoginRegisterScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::CurrencyExchange:
			_showCurrencyExchangeMenu();
			showMainMenu();
			break;
		case enMainMenuOption::Exit:
			_logout();
		}
	}

public:
	static void showMainMenu() {
		system("cls");
		_drawScreenHeader("    Main Screen");
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(56) << "" << "Main Menu Screen\n";
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(48) << "" << "[1] Show Client List.\n";
		cout << setw(48) << "" << "[2] Add New Client.\n";
		cout << setw(48) << "" << "[3] Delete Client.\n";
		cout << setw(48) << "" << "[4] Update Client Info.\n";
		cout << setw(48) << "" << "[5] Find Client.\n";
		cout << setw(48) << "" << "[6] Transactions.\n";
		cout << setw(48) << "" << "[7] Manage Users.\n";
		cout << setw(48) << "" << "[8] Login Register.\n";
		cout << setw(48) << "" << "[9] Currency Exchange.\n";
		cout << setw(48) << "" << "[10] Logout.\n";
		cout << setw(40) << "" << "==================================================\n";

		_performManageUsersMenuOption((enMainMenuOption)_readMainMenuOption());
	}
}; 

