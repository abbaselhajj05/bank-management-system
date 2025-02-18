#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen {
private:
	static void _printCurrencyDataLine(clsCurrency currency) {
		cout << setw(8) << "" << "| " << left << setw(40) << currency.country();
		cout << "| " << left << setw(6) << currency.currencyCode();
		cout << "| " << left << setw(40) << currency.currencyName();
		cout << "| " << left << setw(14) << currency.rate() << endl;
	}

public:
	static void showCurrenciesListScreen() {
		vector<clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();

		_drawScreenHeader("Currencies List Screen", "(" + to_string(vCurrencies.size()) + ") Currency.");
		cout << "\n" << setw(8) << "" << "-------------------------------------------------------------------------------------------------------\n";
		cout << setw(8) << "" << "| " << left << setw(40) << "Country";
		cout << "| " << left << setw(6) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(14) << "Rate/($1)";
		cout << "\n" << setw(8) << "" << "-------------------------------------------------------------------------------------------------------\n";

		if (vCurrencies.size() == 0)
			cout << setw(48) << "" << "No currencies available in the system\n";
		else
			for (clsCurrency& currency : vCurrencies)
				_printCurrencyDataLine(currency);
		cout << setw(8) << "" << "-------------------------------------------------------------------------------------------------------\n";
	}
};

