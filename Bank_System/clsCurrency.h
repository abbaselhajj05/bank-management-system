#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
using namespace std;

class clsCurrency {
private:
	string _country, _currencyCode, _currencyName;
	float _rate;

	clsCurrency(string country, string currencyCode, string currencyName, float rate) : _country(country), _currencyCode(currencyCode), _currencyName(currencyName), _rate(rate) {}

	static clsCurrency _convertLineToCurrencyObject(string dataLine) {
		vector<string> vData = clsString::split(dataLine, "#//#");
		return clsCurrency{ vData[0], vData[1], vData[2], stof(vData[3])};
	}

	static string _convertCurrencyObjectToLine(clsCurrency currency, string seperator = "#//#") {
		string dataLine = "";
		dataLine += currency._country + seperator;
		dataLine += currency._currencyCode + seperator;
		dataLine += currency._currencyName + seperator;
		dataLine += to_string(currency._rate);
		return dataLine;
	}

	static vector <clsCurrency> _loadCurrencyDataFromFile() {
		fstream file;
		file.open("Currencies.txt", ios::in);
		vector<clsCurrency> vCurrencies;

		if (file.is_open()) {
			string dataLine;
			while (getline(file, dataLine)) {
				clsCurrency currency = _convertLineToCurrencyObject(dataLine);
				vCurrencies.push_back(currency);
			}
		}

		file.close();
		return vCurrencies;
	}

	static void _saveCurrencyDataToFile(vector<clsCurrency> vCurrencies) {
		fstream file;
		file.open("Currencies.txt", ios::out);

		if (!(file.is_open()))
			return;

		string dataLine;
		for (clsCurrency& currency : vCurrencies) {
			dataLine = _convertCurrencyObjectToLine(currency);
			file << dataLine << endl;
		}
		file.close();
	}

	void _update() {
		fstream file;
		file.open("Currencies.txt", ios::in);

		if (!file.is_open())
			return;

		vector<clsCurrency> vCurrencies = _loadCurrencyDataFromFile();
		for (clsCurrency& currency : vCurrencies)
			if (currency.currencyCode() == _currencyCode)
				currency = *this;

		_saveCurrencyDataToFile(vCurrencies);
	}

public:

	string country() const {
		return _country;
	}

	string currencyCode() const {
		return _currencyCode;
	}

	string currencyName() const {
		return _currencyName;
	}

	float rate() const {
		return _rate;
	}

	void updateRate(float newRate) {
		_rate = newRate;
		_update();
	}

	static clsCurrency* findByCode(string currencyCode) {
		currencyCode = clsString::toUpperCase(currencyCode);
		clsCurrency* ptr = nullptr;

		fstream file;
		file.open("Currencies.txt", ios::in);
		if (!file.is_open())
			return ptr;

		string dataLine;
		while (getline(file, dataLine)) {
			clsCurrency currency = _convertLineToCurrencyObject(dataLine);
			if (currency._currencyCode == currencyCode) {
				ptr = new clsCurrency(currency);
				break;
			}
		}

		file.close();
		return ptr;
	}

	static clsCurrency* findByCountry(string country) {
		country = clsString::toUpperCase(country);
		clsCurrency* ptr = nullptr;

		fstream file;
		file.open("Currencies.txt", ios::in);
		if (!file.is_open())
			return ptr;

		string dataLine;
		while (getline(file, dataLine)) {
			clsCurrency currency = _convertLineToCurrencyObject(dataLine);
			if (clsString::toUpperCase(currency._country) == country) {
				ptr = new clsCurrency(currency);
				break;
			}
		}

		file.close();
		return ptr;
	}

	static bool currencyExists(string currencyCode) {
		return findByCode(currencyCode);
	}

	static vector<clsCurrency> getCurrenciesList() {
		return _loadCurrencyDataFromFile();
	}

	float convertToUSD(float amount) {
		return amount / _rate;
	}

	float convertToOtherCurrency(float amount, clsCurrency* currencyTo) {
		float amountInUSD = convertToUSD(amount);
		if (currencyTo->_currencyCode == "USD")
			return amountInUSD;
		return amountInUSD * currencyTo->_rate;
	}

};

