#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum enLetterCase { LowerCase, Uppercase };

class clsString {
private:
	string _value;

	static char _toggleLetterCase(char letter) {
		return (isupper(letter) ? tolower(letter) : toupper(letter));
	}

	static bool _isVowel(char letter) {
		string vowels = "aeiou";
		return (vowels.find(letter) != string::npos);
	}

public:
	clsString() : _value("") {}
	clsString(const string value) : _value(value) {}

	static short length(string str) {
		return str.length();
	}

	short length() {
		return _value.length();
	}

	static void printFirstLetterOfEachWord(const string str) {
		bool firstLetter = (str[0] != ' ');
		for (short i = 0; i < str.length(); i++) {
			if (firstLetter)
				cout << str[i] << endl;
			firstLetter = (str[i] == ' ' && str[i + 1] != ' ');
		}
	}

	void printFirstLetterOfEachWord() {
		clsString::printFirstLetterOfEachWord(_value);
	}

	static string capitalizeEachWord(string str) {
		bool firstLetter = (str[0] != ' ');
		for (short i = 0; i < str.length(); i++) {
			if (firstLetter)
				str[i] = toupper(str[i]);
			firstLetter = (str[i] == ' ' && str[i + 1] != ' ');
		}
		return str;
	}

	void capitalizeEachWord() {
		_value = clsString::capitalizeEachWord(_value);
	}

	static string decapitalizeEachWord(string str) {
		bool firstLetter = (str[0] != ' ');
		for (short i = 0; i < str.length(); i++) {
			if (firstLetter)
				str[i] = tolower(str[i]);
			firstLetter = (str[i] == ' ' && str[i + 1] != ' ');
		}
		return str;
	}

	void decapitalizeEachWord() {
		_value = clsString::decapitalizeEachWord(_value);
	}

	static string toUpperCase(string str) {
		for (short i = 0; i < str.length(); i++)
			str[i] = toupper(str[i]);
		return str;
	}

	void toUpperCase() {
		_value = clsString::toUpperCase(_value);
	}

	static string toLowerCase(string str) {
		for (short i = 0; i < str.length(); i++)
			str[i] = tolower(str[i]);
		return str;
	}

	void toLowerCase() {
		_value = clsString::toLowerCase(_value);
	}

	static string toggleCase(string str) {
		for (short i = 0; i < str.length(); i++) {
			str[i] = clsString::_toggleLetterCase(str[i]);
		}
		return str;
	}

	void toggleCase() {
		_value = clsString::toggleCase(_value);
	}

	static short countLettersByCase(string str, enLetterCase letterCase) {
		short lettersCount = 0;
		for (short i = 0; i < str.length(); i++) {
			if ((letterCase == enLetterCase::LowerCase && islower(str[i])) ||
				(letterCase == enLetterCase::Uppercase && isupper(str[i])))
				lettersCount++;
		}
		return lettersCount;
	}

	short countLettersByCase(enLetterCase letterCase) {
		return clsString::countLettersByCase(_value, letterCase);
	}

	static short countLetter(string str, char letter, bool caseSensitive = true) {
		short letterCount = 0;
		for (short i = 0; i < str.length(); i++)
			if ((str[i] == letter) || (tolower(str[i]) == tolower(letter) && !caseSensitive))
				letterCount++;
		return letterCount;
	}

	short countLetter(char letter, bool caseSensitive = true) {
		return clsString::countLetter(_value, letter, caseSensitive);
	}

	static vector<string> split(string str, string delimiter) {
		vector<string> vWords;
		string word;
		short position;
		while ((position = str.find(delimiter)) != string::npos) {
			word = str.substr(0, position);
			//if (word != "")
				vWords.push_back(word);
			str.erase(0, position + delimiter.length());
		}
		if (str != "")
			vWords.push_back(str);
		return vWords;
	}

	vector<string> split(string delimiter) {
		return split(_value, delimiter);
	}

	static short countWords(string str) {
		short wordsCount = 0;
		vector <string> vWords = split(str, " ");
		return vWords.size();
	}

	short countWords() {
		return clsString::countWords(_value);
	}

	static void printWords(string str) {
		vector<string> vWords = split(str, " ");
		for (string& word : vWords)
			cout << word << endl;
	}

	void printWords() {
		clsString::printWords(_value);
	}

	static short countVowels(string str) {
		short vowelsCount = 0;
		for (short i = 0; i < str.length(); i++)
			if (_isVowel(str[i]))
				vowelsCount++;
		return vowelsCount;
	}

	short countVowels() {
		return clsString::countVowels(_value);
	}

	static void printVowels(string str) {
		for (short i = 0; i < str.length(); i++)
			if (_isVowel(str[i]))
				cout << str[i] << endl;
	}

	void printVowels() {
		clsString::printVowels(_value);
	}

	static string leftTrim(string str) {
		short i;
		for (i = 0; str[i] == ' '; i++) {}
		str.erase(0, i);
		return str;
	}

	void leftTrim() {
		_value = clsString::leftTrim(_value);
	}

	static string rightTrim(string str) {
		short i = str.length() - 1;
		while (str[i] == ' ' && i-- >= 0) {}
		return str.substr(0, i + 1);
	}

	void rightTrim() {
		_value = clsString::rightTrim(_value);
	}

	static string trim(string str) {
		return rightTrim(leftTrim(str));
	}

	void trim() {
		_value = clsString::trim(_value);
	}

	static string joinString(vector<string>& vMembers, string delimiter) {
		string str = "";
		for (short i = 0; i < vMembers.size(); i++) {
			str += vMembers[i];
			if (i < vMembers.size() - 1)
				str += delimiter;
		}
		return str;
	}

	static string joinString(string arr[], short arrLength, string delimiter) {
		string str = "";
		for (short i = 0; i < arrLength; i++)
			str += arr[i] + delimiter;
		return str.substr(0, str.length() - delimiter.length());
	}

	static string reverseWords(string str, string delimiter) {
		vector<string> vWords = split(str, delimiter);
		string sReverse = "";
		while (!vWords.empty()) {
			sReverse += vWords.at(vWords.size() - 1) + delimiter;
			vWords.pop_back();
		}
		return sReverse.substr(0, sReverse.length() - delimiter.length());
	}

	void reverseWords(string delimiter = " ") {
		_value = clsString::reverseWords(_value, delimiter);
	}

	static string replace(string str, string sWordToBeReplaced, string sReplacingWord, bool caseSensitive = true) {
		short position;
		if (!caseSensitive) {
			str = toLowerCase(str);
			sWordToBeReplaced = toLowerCase(sWordToBeReplaced);
		}
		while ((position = str.find(sWordToBeReplaced)) != string::npos)
			str.replace(position, sWordToBeReplaced.length(), sReplacingWord);
		return str;
	}

	void replace(string sWordToBeReplaced, string sReplacingWord, bool caseSensitive = true) {
		_value = clsString::replace(_value, sWordToBeReplaced, sReplacingWord, caseSensitive);
	}

	static string removePunctuations(string str) {
		for (short i = 0; i < str.length(); i++)
			if (ispunct(str[i]))
				str.erase(i, 1);
		return str;
	}

	void removePunctuations() {
		_value = clsString::removePunctuations(_value);
	}

	void setValue(const string value) {
		_value = value;
	}

	string getValue() const {
		return _value;
	}

	_declspec(property(get = getValue, put = setValue)) string value;
};