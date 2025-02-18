#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalancesScreen.h";
#include "clsTransferScreen.h";
#include "clsTransferLogScreen.h";
#include "clsInputValidate.h";

class clsTransactionsScreen : protected clsScreen {
private:
	enum enTransactionsMenuOption { Deposit = 1, Withdraw, TotalBalances, Transfer, TransferLog, MainMenu };

	static short _readTransactionsMenuOption() {
		cout << setw(40) << "" << "Choose what do you want to do [1~6]? ";
		short choice = clsInputValidate::readShortNumberBetween(1, 6, "Enter a number between 1 and 6: ");
		return choice;
	}

	static void _goBackToTransactionsMenu() {
		cout << "\n" << setw(40) << "" << "Press any key to go back to Transactions Menu . . . ";
		system("pause > 0");
		showTransactionsMenu();
	}

	static void _showDepositScreen() {
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen() {
		clsWithdrawScreen::showWithdrawScreen();
	}

	static void _showTotalBalancesScreen() {
		clsTotalBalancesScreen::showTotalBalances();
	}

	static void _showTransferScreen() {
		clsTransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen() {
		clsTransferLogScreen::showTransferLogScreen();
	}

	static void _performTransactionsMenuOption(enTransactionsMenuOption transactionMenuOption) {
		system("cls");

		switch (transactionMenuOption) {
		case enTransactionsMenuOption::Deposit:
			_showDepositScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::Withdraw:
			_showWithdrawScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::TotalBalances:
			_showTotalBalancesScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::Transfer:
			_showTransferScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::TransferLog:
			_showTransferLogScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::MainMenu:
			// Do nothing
			break;
		}
	}

public:
	static void showTransactionsMenu() {
		if (!clsScreen::checkAccessRights(clsUser::pTransactionsMenu))
			return;

		system("cls");

		_drawScreenHeader("Transactions Screen");
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(56) << "" << "Transactions Menu\n";
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(48) << "" << "[1] Deposit.\n";
		cout << setw(48) << "" << "[2] Withdraw.\n";
		cout << setw(48) << "" << "[3] Total Balances.\n";
		cout << setw(48) << "" << "[4] Transfer.\n";
		cout << setw(48) << "" << "[5] Transfer Log.\n";
		cout << setw(48) << "" << "[6] Main Menu.\n";
		cout << setw(40) << "" << "==================================================\n";
		
		_performTransactionsMenuOption((enTransactionsMenuOption)_readTransactionsMenuOption());
	}
};

