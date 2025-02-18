#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h";
#include "clsDate.h";
#include "clsUtil.h";
using namespace std;

class clsUser : public clsPerson {
public:
	struct stLoginRegisterRecord {
		string date, time, userName, password;
		int permissions;
	};

	static const short key = 5;	// encryption key

private:
	string _userName, _password;
	int _permissions;

	static clsUser _convertLineToUserObject(string& line, string seperator = "#//#") {
		vector<string> vUserData = clsString::split(line, seperator);
		return clsUser(vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsUtil::decryptText(vUserData[5], key), stoi(vUserData[6]));
	}

	static string _convertUserObjectToLine(clsUser* user, string seperator = "#//#") {
		string dataLine = "";
		dataLine += user->firstName + seperator;
		dataLine += user->lastName + seperator;
		dataLine += user->email + seperator;
		dataLine += user->phone + seperator;
		dataLine += user->_userName + seperator;
		dataLine += clsUtil::encryptText(user->_password, key) + seperator;
		dataLine += to_string(user->_permissions);
		return dataLine;
	}

	static vector<clsUser> _loadUsersDataFromFile() {
		fstream usersFile;
		usersFile.open("Users.txt", ios::in);
		vector<clsUser> vUsers;

		if (usersFile.is_open()) {
			string dataLine;
			while (getline(usersFile, dataLine)) {
				clsUser user = _convertLineToUserObject(dataLine);
				vUsers.push_back(user);
			}
		}

		usersFile.close();
		return vUsers;
	}

	static void _saveUsersDataToFile(vector<clsUser> vUsers) {
		fstream usersFile;
		usersFile.open("Users.txt", ios::out);

		if (!usersFile.is_open())
			return;

		string dataLine;
		for (clsUser& user : vUsers) {
			dataLine = _convertUserObjectToLine(&user);
			usersFile << dataLine << endl;
		}

		usersFile.close();
	}

	static void _addDataLineToFile(string dataLine) {
		fstream usersFile;
		usersFile.open("Users.txt", ios::out | ios::app);

		if (!usersFile.is_open())
			return;

		usersFile << dataLine << endl;
		usersFile.close();
	}

	short _findUserIndex(string userName, vector<clsUser> vUsers) {
		for (short index = 0; index < vUsers.size(); index++)
			if (_userName == vUsers[index]._userName)
				return index;
		return -1;	// user not found
	}

	static stLoginRegisterRecord _convertLoginRegisterLineToRecord(string dataLine, string seperator = "#//#") {
		vector<string> vData = clsString::split(dataLine, seperator);
		vector<string> vDateTime = clsString::split(vData[0], " - ");
		return stLoginRegisterRecord{ vDateTime[0], vDateTime[1], vData[1], clsUtil::decryptText(vData[2], key), stoi(vData[3]) };
	}

	string _prepareLoginRecord(string seperator = "#//#") {
		string dataLine = "";
		dataLine += clsDate().getFormattedDateAndTime() + seperator;
		dataLine += _userName + seperator;
		dataLine += clsUtil::encryptText(_password, key) + seperator;
		dataLine += to_string(_permissions);
		return dataLine;
	}

public:
	enum enPermissions { pAll = -1, pShowClientList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactionsMenu = 32, pManageUsersMenu = 64, pLoginRegister = 128 };

	clsUser(string firstName, string lastName, string email, string phone, string userName, string password, int permissions) :
		clsPerson(firstName, lastName, email, phone), _userName(userName), _password(password), _permissions(permissions) {}

	static bool userExists(string userName) {
		return find(userName);
	}

	static bool userExists(string userName, string password) {
		return find(userName, password);
	}

	void setUserName(const string userName) {
		_userName = userName;
	}

	string getUserName() const {
		return _userName;
	}

	void setPassword(const string password) {
		_password = password;
	}

	string getPassword() const {
		return _password;
	}

	void setPermissions(const int permissions) {
		_permissions = permissions;
	}

	int getPermissions() const {
		return _permissions;
	}

	_declspec(property(get = getUserName, put = setUserName)) string userName;
	_declspec(property(get = getPassword, put = setPassword)) string password;
	_declspec(property(get = getPermissions, put = setPermissions)) int permissions;

	static clsUser createWithUserName(string userName) {
		return clsUser("", "", "", "", userName, "", 0);
	}

	static clsUser* find(string userName) {
		fstream file;
		file.open("Users.txt", ios::in);
		clsUser* ptr = nullptr;

		if (!file.is_open())
			return ptr;

		string lineRecord;
		while (getline(file, lineRecord)) {
			clsUser user = _convertLineToUserObject(lineRecord);
			if (user._userName == userName) {
				ptr = new clsUser(user);
				break;
			}
		}

		file.close();
		return ptr;
	}

	static clsUser* find(string userName, string password) {
		fstream file;
		file.open("Users.txt", ios::in);
		clsUser* ptr = nullptr;

		if (!file.is_open())
			return ptr;

		string lineRecord;
		while (getline(file, lineRecord)) {
			clsUser user = _convertLineToUserObject(lineRecord);
			if (user._userName == userName && user.password == password) {
				ptr = new clsUser(user);
				break;
			}
		}

		file.close();
		return ptr;
	}

	void update() {
		vector<clsUser> vUsers = _loadUsersDataFromFile();
		for (clsUser& client : vUsers)
			if (_userName == client._userName) {
				client = *this;
				break;
			}
		_saveUsersDataToFile(vUsers);
	}

	bool add() {
		if (userExists(_userName))
			return false;

		string dataLine = _convertUserObjectToLine(this);
		_addDataLineToFile(dataLine);
		return true;
	}

	bool Delete() {
		vector<clsUser> vClients = _loadUsersDataFromFile();

		short clientIndex = _findUserIndex(_userName, vClients);
		if (clientIndex == -1)
			return false;

		vClients.erase(vClients.begin() + clientIndex);
		_saveUsersDataToFile(vClients);
		return true;
	}

	static vector<clsUser> getUsersList() {
		return _loadUsersDataFromFile();
	}

	bool checkAccessPermission(clsUser::enPermissions permission) {
		return ((permission | _permissions) == _permissions);
	}

	void registerLogin() {
		fstream logFile;
		logFile.open("LoginRegister.txt", ios::out | ios::app);

		if (!logFile.is_open())
			return;

		logFile << _prepareLoginRecord() << endl;
		logFile.close();
	}

	static vector<stLoginRegisterRecord> getLoginRegisterList() {
		fstream logFile;
		logFile.open("LoginRegister.txt", ios::in);
		vector<stLoginRegisterRecord> vRecords;

		if (logFile.is_open()) {
			string record;
			while (getline(logFile, record)) {
				vRecords.push_back(_convertLoginRegisterLineToRecord(record));
			}
		}

		logFile.close();
		return vRecords;
	}

};

