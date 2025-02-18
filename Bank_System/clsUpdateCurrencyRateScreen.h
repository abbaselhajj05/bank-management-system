#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen {
private:
	static float _readRate() {
		cout << "\nEnter new rate: ";
		float newRate = clsInputValidate::readFloatNumber();
		return newRate;
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
	static void showUpdateCurrencyRateScreen() {
		_drawScreenHeader("Update Currency Screen");

		string currencyCode;
		cout << "Please enter Currency Code: ";
		currencyCode = clsInputValidate::readString();

		clsCurrency* currency = nullptr;
		while (true) {
			currency = clsCurrency::findByCode(currencyCode);
			if (currency)
				break;
			cout << "\nCurrency was not found!\nChoose another one:";
			currencyCode = clsInputValidate::readString();
		}

		_printCurrency(currency);
		cout << "\nAre you sure you want to update the rate of this currency [Y/N]? ";
		char confirmUpdate = clsInputValidate::readChar();
		if (toupper(confirmUpdate) != 'Y')
			return;

		cout << "\nUpdate Currency Rate:";
		cout << "\n---------------------";
	
		currency->updateRate(_readRate());
		cout << "\nCurrency Rate Updated Successfully!\n";
		_printCurrency(currency);

		delete currency;
		currency = nullptr;
	}
};

