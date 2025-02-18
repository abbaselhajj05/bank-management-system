#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h";
#include "clsPerson.h";
using namespace std;

class clsBankClient : public clsPerson {
public:
	struct stTransferLogRecord {
		string date, time, senderAccountNumber, receiverAccountNumber;
		double amount, senderAccountBalanceAfter, receiverAccountBalanceAfter;
		string userName;
	};
private:
	string _accountNumber, _pinCode;
	double _accountBalance;

	static clsBankClient _convertLineToClientObject(string& line, string seperator = "#//#") {
		vector<string> vClientData = clsString::split(line, seperator);
		return clsBankClient(vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
	}

	static string _convertClientObjectToLine(clsBankClient* client, string seperator = "#//#") {
		string dataLine = "";
		dataLine += client->firstName + seperator;
		dataLine += client->lastName + seperator;
		dataLine += client->email + seperator;
		dataLine += client->phone + seperator;
		dataLine += client->_accountNumber + seperator;
		dataLine += client->_pinCode + seperator;
		dataLine += to_string(client->_accountBalance);
		return dataLine;
	}

	static vector<clsBankClient> _loadClientsDataFromFile() {
		fstream clientsFile;
		clientsFile.open("Clients.txt", ios::in);
		vector<clsBankClient> vClients;

		if (clientsFile.is_open()) {
			string dataLine;
			while (getline(clientsFile, dataLine)) {
				clsBankClient client = _convertLineToClientObject(dataLine);
				vClients.push_back(client);
			}
		}

		clientsFile.close();
		return vClients;
	}

	static void _saveClientsDataToFile(vector<clsBankClient> vClients) {
		fstream clientsFile;
		clientsFile.open("Clients.txt", ios::out);

		if (!clientsFile.is_open())
			return;

		string dataLine;
		for (clsBankClient& client : vClients) {
			dataLine = _convertClientObjectToLine(&client);
			clientsFile << dataLine << endl;
		}

		clientsFile.close();
	}

	static void _addDataLineToFile(string dataLine) {
		fstream clientsFile;
		clientsFile.open("Clients.txt", ios::out | ios::app);

		if (!clientsFile.is_open())
			return;

		clientsFile << dataLine << endl;
		clientsFile.close();
	}

	short _findClientIndex(string accountNumber, vector<clsBankClient> vClients) {
		for (short index = 0; index < vClients.size(); index++)
			if (accountNumber == vClients[index].accountNumber())
				return index;
		return -1;	// client not found
	}

	static stTransferLogRecord _convertLineToTransferLogRecord(string dataLine, string delimiter = "#//#") {
		vector<string> vData = clsString::split(dataLine, delimiter);
		vector<string> vDateAndTime = clsString::split(vData[0], " - ");
		return stTransferLogRecord{ vDateAndTime[0], vDateAndTime[1], vData[1], vData[2], stod(vData[3]), stod(vData[4]), stod(vData[5]), vData[6] };
	}

	string _prepareTransferLogRecord(double amount, clsBankClient& receiverClient, string userName, string seperator = "#//#") {
		string dataLine = "";
		dataLine += clsDate().getFormattedDateAndTime() + seperator;
		dataLine += _accountNumber + seperator;
		dataLine += receiverClient.accountNumber() + seperator;
		dataLine += to_string(amount) + seperator;
		dataLine += to_string(_accountBalance) + seperator;
		dataLine += to_string(receiverClient.accountBalance) + seperator;
		dataLine += userName;
		return dataLine;
	}

public:
	clsBankClient(string firstName, string lastName, string email, string phone, string accountNumber, string pinCode, float accountBalance)
		: clsPerson(firstName, lastName, email, phone), _accountNumber(accountNumber), _pinCode(pinCode), _accountBalance(accountBalance) {}

	static bool clientExists(string accountNumber) {
		return find(accountNumber);
	}

	string accountNumber() const {
		return _accountNumber;
	}

	void setPinCode(const string pinCode) {
		_pinCode = pinCode;
	}

	string getPinCode() const {
		return _pinCode;
	}

	void setAccountBalance(double accountBalance) {
		_accountBalance = accountBalance;
	}

	double getAccountBalance() const {
		return _accountBalance;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double accountBalance;

	//	No UI-Related code inside object.

	/*void print() override {
		if (!this) return;

		cout << "\nClient Card:";
		cout << "\n----------------------------------------";
		cout << "\nFirst name     : " << firstName;
		cout << "\nLast name      : " << lastName;
		cout << "\nFull name      : " << fullName();
		cout << "\nEmail          : " << email;
		cout << "\nPhone          : " << phone;
		cout << "\nAccount Number : " << _accountNumber;
		cout << "\nPassword       : " << _pinCode;
		cout << "\nBalance        : " << _accountBalance;
		cout << "\n----------------------------------------\n";
	}*/

	static clsBankClient createWithAccountNumber(string accountNumber) {
		return clsBankClient("", "", "", "", accountNumber, "", 0);
	}

	static clsBankClient* find(string accountNumber) {
		fstream file;
		file.open("Clients.txt", ios::in);
		clsBankClient* ptr = nullptr;

		if (!file.is_open())
			return ptr;

		string dataLine;
		while (getline(file, dataLine)) {
			clsBankClient client = _convertLineToClientObject(dataLine);
			if (client._accountNumber == accountNumber) {
				ptr = new clsBankClient(client);
				break;
			}
		}

		file.close();
		return ptr;
	}

	static clsBankClient* find(string accountNumber, string pinCode) {
		fstream file;
		file.open("Clients.txt", ios::in);
		clsBankClient* ptr = nullptr;

		if (!file.is_open())
			return ptr;
		
		string dataLine;
		while (getline(file, dataLine)) {
			clsBankClient client = _convertLineToClientObject(dataLine);
			if (client._accountNumber == accountNumber && client._pinCode == pinCode) {
				ptr = new clsBankClient(client);
				break;
			}
		}

		file.close();
		return ptr;
	}

	void update() {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& client : vClients)
			if (_accountNumber == client._accountNumber) {
				client = *this;
				break;
			}
		_saveClientsDataToFile(vClients);
	}

	bool add() {
		if (clientExists(_accountNumber))
			return false;

		string dataLine = _convertClientObjectToLine(this);
		_addDataLineToFile(dataLine);
		return true;
	}

	bool Delete() {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		short clientIndex = _findClientIndex(_accountNumber, vClients);
		if (clientIndex == -1)
			return false;
		
		vClients.erase(vClients.begin() + clientIndex);
		_saveClientsDataToFile(vClients);
		return true;
	}

	static vector<clsBankClient> getClientsList() {
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances() {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		double totalBalances = 0;
		for (clsBankClient& client : vClients)
			totalBalances += client.accountBalance;

		return totalBalances;
	}

	bool deposit(float amount) {
		if (amount <= 0)
			return false;
		_accountBalance += amount;
		update();
		return true;
	}

	bool withdraw(float amount) {
		if (amount > _accountBalance)
			return false;
		_accountBalance -= amount;
		update();
		return true;
	}

	void registerTranferLog(double amount, clsBankClient& receiverClient, string userName) {
		fstream logFile;
		logFile.open("TransferLog.txt", ios::out | ios::app);

		if (!logFile.is_open())
			return;

		logFile << _prepareTransferLogRecord(amount, receiverClient, userName) << endl;
		logFile.close();
	}

	bool transfer(double amount, clsBankClient& receiverClient, string userName) {
		if (!withdraw(amount))
			return false;
		receiverClient.deposit(amount);
		registerTranferLog(amount, receiverClient, userName);
		return true;
	}

	static vector<stTransferLogRecord> getTransferLogRecords() {
		fstream logFile;
		logFile.open("TransferLog.txt", ios::in);
		vector<stTransferLogRecord> vRecords;

		if (logFile.is_open()) {
			string dataLine;
			while (getline(logFile, dataLine))
				vRecords.push_back(_convertLineToTransferLogRecord(dataLine));
		}

		logFile.close();
		return vRecords;
	}

};

