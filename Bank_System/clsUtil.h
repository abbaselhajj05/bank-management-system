#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "clsDate.h";
using namespace std;

class clsUtil {
public:
	enum enCharType { SmallLetter = 1, CapitalLetter, Digit, SpecialChar, RandomChar };

	static void sRand() {
		// Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to) {
		return (rand() % (to - from + 1)) + from;
	}

	static void swap(int& a, int& b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	static void swap(double& a, double& b) {
		double tmp = a;
		a = b;
		b = tmp;
	}

	static void swap(bool& a, bool& b) {
		bool tmp = a;
		a = b;
		b = tmp;
	}

	static void swap(char& a, char& b) {
		char tmp = a;
		a = b;
		b = tmp;
	}

	static void swap(string& a, string& b) {
		string tmp = a;
		a = b;
		b = tmp;
	}

	static void swap(clsDate& date1, clsDate& date2) {
		clsDate tmpDate = date1;
		date1 = date2;
		date2 = tmpDate;
	}

	static char getRandomCharacter(enCharType charType) {
		if (charType == enCharType::RandomChar)
			charType = (enCharType)randomNumber(1, 3);

		switch (charType) {
		case enCharType::SmallLetter:
			return (char)randomNumber(97, 122);
		case enCharType::CapitalLetter:
			return (char)randomNumber(65, 90);
		case enCharType::Digit:
			return (char)randomNumber(48, 57);
		case enCharType::SpecialChar:
			return (char)randomNumber(33, 47);
		}
	}

	static string generateWord(enCharType charType, short slotLength = 4) {
		string word = "";
		for (short i = 1; i <= slotLength; i++)
			word += getRandomCharacter(charType);
		return word;
	}

	static string generateKey(enCharType charType, short slotLength = 4) {
		string key = "";
		for (short i = 1; i <= 4; i++) {
			key += generateWord(charType, slotLength);
			if (i < 4)
				key += "-";
		}
		return key;
	}

	static vector<string> generateKeys(short numberOfKeys, enCharType charType, short slotLength = 4) {
		vector<string> arrKeys;
		for (short key = 0; key < numberOfKeys; key++) {
			arrKeys.push_back(generateKey(charType, slotLength));
		}
		return arrKeys;
	}

	static void fillArrayWithRandomNumbers(int* arr, short arrLength, int from, int to) {
		for (short i = 0; i < arrLength; i++)
			*(arr + i) = randomNumber(from, to);
	}

	static void fillArrayWithRandomWords(string* arr, short arrLength, enCharType charType, short slotLength = 4) {
		for (short i = 0; i < arrLength; i++)
			*(arr + i) = generateWord(charType, slotLength);
	}

	static void fillArrayWithRandomKeys(string* arr, short arrLength, enCharType charType, short slotLength = 4) {
		for (short i = 0; i < arrLength; i++)
			*(arr + i) = generateKey(charType, slotLength);
	}

	static void shuffleArray(int* arr, short arrLength) {
		for (short i = 0; i < arrLength; i++)
			swap(arr[i], arr[randomNumber(0, arrLength - 1)]);
	}

	static void shuffleArray(string* arr, short arrLength) {
		for (short i = 0; i < arrLength; i++)
			swap(arr[i], arr[randomNumber(0, arrLength - 1)]);
	}

	static string tabs(short numberOfTabs) {
		string sTabs = "";
		for (short i = 1; i <= numberOfTabs; i++)
			sTabs += "\t";
		return sTabs;
	}

	static string encryptText(string text, short encryptionKey = 2) {
		for (int i = 0; i < text.length(); i++)
			text[i] += encryptionKey;
		return text;
	}

	static string decryptText(string text, short encryptionKey = 2) {
		for (int i = 0; i < text.length(); i++)
			text[i] -= encryptionKey;
		return text;
	}

	static string numberToText(int number) {
		if (number == 0)
			return "";
		if (number >= 1 && number <= 19) {
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
						"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return arr[number];
		}
		if (number >= 20 && number <= 99) {
			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			return arr[number / 10] + " " + numberToText(number % 10);
		}
		if (number >= 100 && number <= 199)
			return "One Hundred " + numberToText(number % 100);

		if (number >= 200 && number <= 999)
			return numberToText(number / 100) + " Hundreds " + numberToText(number % 100);

		if (number >= 1000 && number <= 1999)
			return "One Thousand " + numberToText(number % 1000);

		if (number >= 2000 && number <= 999999)
			return numberToText(number / 1000) + " Thousands " + numberToText(number % 1000);

		if (number >= 1000000 && number <= 1999999)
			return "One Million " + numberToText(number % 1000000);

		if (number >= 2000000 && number <= 199999999)
			return numberToText(number / 1000000) + " Millions " + numberToText(number % 1000000);

		if (number >= 1000000000 && number <= 1999999999)
			return "One Billion " + numberToText(number % 1000000);

		if (number >= 2000000000 && number <= 999999999999)
			return numberToText(number / 1000000000) + " Billions " + numberToText(number % 1000000000);
	}
};

