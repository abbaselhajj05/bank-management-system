#pragma once
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen {
private:
	enum enCurrencyExchangeMenuOption { ListCurrencies = 1, FindCurrency, UpdateRate, CurrencyCalculator, MainMenu };

	static short _readCurrencyExchangeMenuOption() {
		cout << setw(40) << "" << "Choose what do you want to do [1~5]? ";
		short choice = clsInputValidate::readShortNumberBetween(1, 5, "Enter a number between 1 and 5: ");
		return choice;
	}

	static void _goBackToCurrencyExchangeMenu() {
		cout << "\n" << setw(40) << "" << "Press any key to go back to Currency Exchange Menu . . . ";
		system("pause > 0");
		showCurrencyExchangeMenu();
	}

	static void _showListCurrenciesScreen() {
		/*cout << "List Currencies Screen will be here!\n";*/
		clsCurrenciesListScreen::showCurrenciesListScreen();
	}

	static void _showFindCurrencyScreen() {
		/*cout << "Find Currency Screen will be here\n";*/
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _showUpdateRateScreen() {
		/*cout << "Update Rate Screen will be here!\n";*/
		clsUpdateCurrencyRateScreen::showUpdateCurrencyRateScreen();
	}

	static void _showCurrencyCalculator() {
		/*cout << "Currency Calculator will be here!\n";*/
		clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _performExchangeCurrencyMenuOption(enCurrencyExchangeMenuOption currencyExchangeMenuOption) {
		system("cls");
		switch (currencyExchangeMenuOption) {
		case clsCurrencyExchangeScreen::ListCurrencies:
			_showListCurrenciesScreen();
			_goBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::FindCurrency:
			_showFindCurrencyScreen();
			_goBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::UpdateRate:
			_showUpdateRateScreen();
			_goBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::CurrencyCalculator:
			_showCurrencyCalculator();
			_goBackToCurrencyExchangeMenu();
			break;
		case clsCurrencyExchangeScreen::MainMenu:
			break;
		}
	}

public:
	static void showCurrencyExchangeMenu() {
		system("cls");
		_drawScreenHeader("Currency Exchange Main Screen");
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(56) << "" << "Currency Exchange Menu\n";
		cout << setw(40) << "" << "==================================================\n";
		cout << setw(48) << "" << "[1] List Currencies.\n";
		cout << setw(48) << "" << "[2] Find Currency.\n";
		cout << setw(48) << "" << "[3] Update Rate.\n";
		cout << setw(48) << "" << "[4] Currency Calculator.\n";
		cout << setw(48) << "" << "[5] Main Menu.\n";
		cout << setw(40) << "" << "==================================================\n";

		_performExchangeCurrencyMenuOption((enCurrencyExchangeMenuOption)_readCurrencyExchangeMenuOption());
	}
};

