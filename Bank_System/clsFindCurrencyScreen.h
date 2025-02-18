#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen {
private:
	enum enFindCurrencyMethod { ByCode = 1, ByCountry };

	static clsCurrency* _readCurrency(enFindCurrencyMethod method) {
		clsCurrency* currency = nullptr;

		switch (method) {
			case clsFindCurrencyScreen::ByCode: {
				cout << "\nPlease enter Currency Code: ";
				string currencyCode = clsInputValidate::readString();
				currency = clsCurrency::findByCode(currencyCode);
			}
				break;
			case clsFindCurrencyScreen::ByCountry: {
				cout << "\nPlease enter Country Name: ";
				string country = clsInputValidate::readString();
				currency = clsCurrency::findByCountry(country);
			}
		}

		return currency;
	}

	static void _printCurrency(clsCurrency* currency) {
		cout << "\nCurrency Card:";
		cout << "\n----------------------------------------";
		cout << "\nCountry   : " << currency->country();
		cout << "\nCode      : " << currency->currencyCode();
		cout << "\nName      : " << currency->currencyName();
		cout << "\nRate ($1) : " << currency->rate();
		cout << "\n----------------------------------------\n";
	}

public:
	static void showFindCurrencyScreen() {
		_drawScreenHeader("Find Currency Screen");

		cout << "Find by: [1] Code or [2] Country? ";
		short findMethod = clsInputValidate::readShortNumberBetween(1, 2, "Enter either [1] or [2]: ");

		clsCurrency* currency = nullptr;
		currency = _readCurrency((enFindCurrencyMethod) findMethod);
		
		if (currency)
			_printCurrency(currency);
		else
			cout << "\nCurrency not found!";

		delete currency;
		currency = nullptr;
	}
};

