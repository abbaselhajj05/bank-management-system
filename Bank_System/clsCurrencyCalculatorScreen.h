#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen {
private:
	static float _readAmount() {
		cout << "\nEnter amount to exchange: ";
		float amount = clsInputValidate::readPositiveFloatNumber();
		return amount;
	}

	static clsCurrency* _readCurrency(string message) {
		cout << message;
		string currencyCode = clsInputValidate::readString();

		clsCurrency* currency = nullptr;
		while (true) {
			currency = clsCurrency::findByCode(currencyCode);
			if (currency)
				break;
			cout << "\nCurrency was not found!\nChoose another one: ";
			currencyCode = clsInputValidate::readString();
		}
		return currency;
	}

	static void _printCurrencyCard(clsCurrency* currency) {
		cout << "\nCurrency Card:";
		cout << "\n----------------------------------------";
		cout << "\nCountry   : " << currency->country();
		cout << "\nCode      : " << currency->currencyCode();
		cout << "\nName      : " << currency->currencyName();
		cout << "\nRate ($1) : " << currency->rate();
		cout << "\n----------------------------------------\n";
	}

	static void _printCalculationResults(float amount, clsCurrency* currencyFrom, clsCurrency* currencyTo) {
		cout << "\nConvert from: " << currencyFrom->currencyCode() << " to " << currencyTo->currencyCode() << endl;
		_printCurrencyCard(currencyFrom);

		float amountInUSD = amount;
		if (currencyFrom->currencyCode() != "USD") {
			cout << "\nConverting from " << currencyFrom->currencyCode() << " to USD...\n";
			amountInUSD = currencyFrom->convertToUSD(amount);
			cout << amount << " " << currencyFrom->currencyCode() << " = " << amountInUSD << " USD\n";
		}

		if (currencyTo->currencyCode() == "USD")
			return;

		_printCurrencyCard(currencyTo);
		
		cout << "\nConverting from USD to " << currencyTo->currencyCode() << "...\n";
		float amountInOtherCurrency = currencyFrom->convertToOtherCurrency(amountInUSD, currencyTo);
		cout << amount << " " << currencyFrom->currencyCode() << " = " << amountInOtherCurrency << " " << currencyTo->currencyCode() << "\n";
	}

	static void _performCurrencyCalculation() {
		clsCurrency* currencyFrom = _readCurrency("Please enter Currency1 Code: ");
		clsCurrency* currencyTo = _readCurrency("\nPlease enter Currency2 Code: ");

		while (currencyFrom->currencyCode() == currencyTo->currencyCode()) {
			cout << "\nCan't convert to same currency!\n";
			currencyTo = _readCurrency("Please enter Currency2 Code: ");
		}

		float amount = _readAmount();
		_printCalculationResults(amount, currencyFrom, currencyTo);

		delete currencyFrom, currencyTo;
		currencyFrom = currencyTo = nullptr;
	}

public:
	static void showCurrencyCalculatorScreen() {
		char calculateMore;

		do {
			system("cls");
			_drawScreenHeader("Currency Calculator Screen");
			_performCurrencyCalculation();
			cout << "\nDo you want to perform any other calculation [Y/N]? ";
			calculateMore = clsInputValidate::readChar();
		} while (toupper(calculateMore) == 'Y');
	}
};

