#pragma once
#include <iostream>
#include "InterfaceCommunication.h"
using namespace std;

class clsPerson : public InterfaceCommunication {
private:
	string _firstName, _lastName, _email, _phone;
public:
	clsPerson(string firstName, string lastName, string email, string phone) : _firstName(firstName), _lastName(lastName), _phone(phone), _email(email) {}

	void setFirstName(const string firstName) {
		_firstName = firstName;
	}

	string getFirstName() const {
		return _firstName;
	}

	void setLastName(const string lastName) {
		_lastName = lastName;
	}

	string getLastName() const {
		return _lastName;
	}

	void setEmail(const string email) {
		_email = email;
	}

	string getEmail() const {
		return _email;
	}

	void setPhone(const string phone) {
		_phone = phone;
	}

	string getPhone() const {
		return _phone;
	}

	_declspec(property(get = getFirstName, put = setFirstName)) string firstName;
	_declspec(property(get = getLastName, put = setLastName)) string lastName;
	_declspec(property(get = getEmail, put = setEmail)) string email;
	_declspec(property(get = getPhone, put = setPhone)) string phone;

	string fullName() {
		return _firstName + " " + _lastName;
	}

	virtual void print() {
		cout << "\n----------------------------------------";
		cout << "\nFirst name : " << _firstName;
		cout << "\nLast name  : " << _lastName;
		cout << "\nFull name  : " << fullName();
		cout << "\nEmail      : " << _email;
		cout << "\nPhone      : " << _phone;
		cout << "\n----------------------------------------\n";
	}

	// It is obligatory to define all interface methods (override)
	void sendEmail(string title, string body) override {

	}

	void sendFax(string title, string body) override {

	}

	void sendSMS(string title, string body) override {

	}

};
