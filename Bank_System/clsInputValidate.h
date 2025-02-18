#pragma once
#include <iostream>
#include <limits>
#include "clsDate.h";

class clsInputValidate {
public:
	static bool isNumberBetween(short number, short from, short to) {
		return (number >= from && number <= to);
	}

	static bool isNumberBetween(int number, int from, int to) {
		return (number >= from && number <= to);
	}

	static bool isNumberBetween(float number, float from, float to) {
		return (number >= from && number <= to);
	}

	static bool isNumberBetween(double number, double from, double to) {
		return (number >= from && number <= to);
	}

	static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo) {
		if (dateFrom.isAfter(dateTo))
			clsDate::swapDates(dateFrom, dateTo);
		return !(date.isBefore(dateFrom) || date.isAfter(dateTo));
	}

	static short readShortNumber(string errorMessage = "Invalid number, enter a valid one: ") {
		short number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static int readIntNumber(string errorMessage = "Invalid number, enter a valid one: ") {
		int number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static float readFloatNumber(string errorMessage = "Invalid number, enter a valid one: ") {
		float number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static double readDblNumber(string errorMessage = "Invalid number, enter a valid one: ") {
		double number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static double readChar(string errorMessage = "Invalid character, enter a valid one: ") {
		char c;
		cin >> c;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
			cin >> c;
		}
		return c;
	}

	static short readShortNumberBetween(short from, short to, string errorMessage) {
		short number;
		while (true) {
			number = readShortNumber();
			if (isNumberBetween(number, from, to))
				break;
			cout << errorMessage;
		}
		return number;
	}

	static int readIntNumberBetween(int from, int to, string errorMessage) {
		int number;
		while (true) {
			number = readIntNumber();
			if (isNumberBetween(number, from, to))
				break;
			cout << errorMessage;
		}
		return number;
	}

	static short readPositiveShortNumber(string errorMessage = "Please enter a positive number: ") {
		short number;
		while (true) {
			number = readShortNumber();
			if (number > 0)
				break;
			cout << errorMessage;
		}
		return number;
	}

	static float readPositiveFloatNumber(string errorMessage = "Please enter a positive number: ") {
		float number;
		while (true) {
			number = readFloatNumber();
			if (number > 0)
				break;
			cout << errorMessage;
		}
		return number;
	}

	static short readPositiveDblNumber(string errorMessage = "Please enter a positive number: ") {
		double number;
		while (true) {
			number = readDblNumber();
			if (number > 0)
				break;
			cout << errorMessage;
		}
		return number;
	}

	static string readString() {
		string s1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, s1);
		return s1;
	}

	static bool isValidDate(clsDate date) {
		return date.isValid();
	}
};
