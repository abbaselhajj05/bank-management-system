#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include "clsString.h";
using namespace std;

class clsDate {
private:
	short _day, _month, _year, _hour, _minute, _second;
	enum _enDayOfWeek { Sun, Mon, Tue, Wed, Thu, Fri, Sat };
	enum _enMonth { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
	enum _enDateComparisonResult { Before = -1, Equal, After };

	static void _correctDate(clsDate& date) {
		short maxMonthDays = clsDate::daysInMonth(date._month, date._year);
		if (date._day > maxMonthDays)
			date._day = maxMonthDays;
	}

public:
	clsDate() {
		*this = clsDate::getLocalDate();
	}

	clsDate(string sDate) {
		*this = parseDate(sDate);
	}

	clsDate(short day, short month, short year) : _day(day), _month(month), _year(year) {}

	clsDate(short day, short month, short year, short hour, short minute, short second) : _day(day), _month(month), _year(year), _hour(hour), _minute(minute), _second(second) {}

	clsDate(short daysFromStartOfYear, short year) {
		*this = clsDate::addDays(clsDate(1, 1, year), daysFromStartOfYear - 1);
	}

	static void swapDates(clsDate& date1, clsDate& date2) {
		clsDate tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	static bool isLeapYear(short year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool isLeapYear() {
		return clsDate::isLeapYear(_year);
	}

	static short daysInYear(short year) {
		return isLeapYear(year) ? 366 : 365;
	}

	short daysInYear() {
		return clsDate::daysInYear(_year);
	}

	static short daysInMonth(short month, short year) {
		short monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return month == _enMonth::Feb ? (isLeapYear(year) ? 29 : 28) : monthDays[month - 1];
	}

	short daysInMonth() {
		return clsDate::daysInMonth(_month, _year);
	}

	static short hoursInYear(short year) {
		return daysInYear(year) * 24;
	}

	short hoursInYear() {
		return clsDate::hoursInYear(_year);
	}

	static short hoursInMonth(short month, short year) {
		return clsDate::daysInMonth(month, year) * 24;
	}

	short hoursInMonth() {
		return clsDate::hoursInMonth(_month, _year);
	}

	static int minutesInYear(short year) {
		return clsDate::hoursInYear(year) * 60;
	}

	int minutesInYear() {
		return clsDate::minutesInYear(_year);
	}

	static int minutesInMonth(short month, short year) {
		return clsDate::hoursInMonth(month, year) * 60;
	}

	int minutesInMonth() {
		return clsDate::minutesInMonth(_month, _year);
	}

	static int secondsInYear(short year) {
		return clsDate::minutesInYear(year) * 60;
	}

	int secondsInYear() {
		return clsDate::secondsInYear(_year);
	}

	static int secondsInMonth(short month, short year) {
		return clsDate::minutesInMonth(month, year) * 60;
	}

	int secondsInMonth() {
		return clsDate::secondsInMonth(_month, _year);
	}

	static short getDayOfWeek(clsDate date) {
		short a = abs((14 - date._month) / 12);
		short y = date._year - a;
		short m = date._month + 12 * a - 2;

		short dayOfWeek = ((date._day + y + abs(y / 4) - abs(y / 100) + abs(y / 400) + abs(31 * m) / 12) % 7);
		return dayOfWeek;
	}

	short getDayOfWeek() {
		return clsDate::getDayOfWeek(*this);
	}

	static string getMonthName(short month) {
		string arrMonths[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrMonths[month - 1];
	}

	string getMonthName() {
		return clsDate::getMonthName(_month);
	}

	static string getDayName(short dayOrder) {
		string arrDays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return arrDays[dayOrder];
	}

	string getDayName() {
		return clsDate::getDayName(getDayOfWeek(*this));
	}

	static void printMonthCalendar(short month, short year) {
		cout << "\n ____________" << clsDate::getMonthName(month) << "____________\n";
		cout << "\n Sun Mon Tue Wed Thu Fri Sat\n";

		short i;
		short firstDayOfWeek = clsDate::getDayOfWeek(clsDate(1, month, year));
		for (i = 0; i < firstDayOfWeek; i++)
			cout << setw(4) << "";

		for (short dayNumber = 1; dayNumber <= clsDate::daysInMonth(month, year); dayNumber++) {
			cout << right << setw(4) << dayNumber;
			if (i++ == 6) {
				cout << endl;
				i = 0;
			}
		}

		cout << "\n ___________________________\n";
	}

	void printMonthCalendar() {
		clsDate::printMonthCalendar(_month, _year);
	}

	static void printYearCalendar(short year) {
		cout << "\n ___________________________\n";
		cout << "\n       Calendar - " << year << "\n";
		cout << "\n ___________________________\n";
		for (short month = 1; month <= 12; month++)
			printMonthCalendar(month, year);
	}

	void printYearCalendar() {
		clsDate::printYearCalendar(_year);
	}

	static short daysFromStartOfYear(clsDate date) {
		short numberOfDays = 0;
		for (short month = 1; month < date._month; month++)
			numberOfDays += clsDate::daysInMonth(month, date._year);
		numberOfDays += date._day;
		return numberOfDays;
	}

	short daysFromStartOfYear() {
		return clsDate::daysFromStartOfYear(*this);
	}

	static short daysUntilEndOfWeek(clsDate date) {
		return _enDayOfWeek::Sat - date.getDayOfWeek();
	}

	short daysUntilEndOfWeek() {
		return clsDate::daysUntilEndOfWeek(*this);
	}

	static short daysUntilEndOfMonth(clsDate date) {
		return date.daysInMonth() - date._day + 1;	// Including end date
	}

	short daysUntilEndOfMonth() {
		return clsDate::daysUntilEndOfMonth(*this);
	}

	static short daysUntilEndOfYear(clsDate date) {
		return date.daysInYear() - date.daysFromStartOfYear();
	}

	short daysUntilEndOfYear() {
		return clsDate::daysUntilEndOfYear(*this);
	}

	static clsDate convertDaysToDate(short numberOfDays, short year) {
		short monthDays, month = 1;
		while (numberOfDays > (monthDays = clsDate::daysInMonth(month, year))) {
			numberOfDays -= monthDays;
			month++;
		}
		return clsDate(numberOfDays, month, year);
	}

	static bool isBefore(clsDate& date1, clsDate date2) {
		return (date1._year < date2._year)
			? true : (date1._year > date2._year)
			? false : (date1._month < date2._month)
			? true : (date1._month > date2._month)
			? false : (date1._day < date2._day);
	}

	bool isBefore(clsDate& other) {
		return clsDate::isBefore(*this, other);
	}

	static bool isEqual(clsDate& date1, clsDate& date2) {
		return (date1._day == date2._day && date1._month == date2._month && date1._year == date2._year);
	}

	bool isEqual(clsDate& other) {
		return clsDate::isEqual(*this, other);
	}

	static bool isAfter(clsDate date1, clsDate date2) {
		return !(date1.isBefore(date2) || date1.isEqual(date2));
	}

	bool isAfter(clsDate other) {
		return clsDate::isAfter(*this, other);
	}

	static _enDateComparisonResult compareDates(clsDate& date1, clsDate& date2) {
		if (date1.isBefore(date2))
			return _enDateComparisonResult::Before;
		if (date1.isEqual(date2))
			return _enDateComparisonResult::Equal;
		return _enDateComparisonResult::After;
	}

	_enDateComparisonResult compareTo(clsDate& other) {
		return clsDate::compareDates(*this, other);
	}

	static bool isLastDayInMonth(clsDate& date) {
		return date._day == clsDate::daysInMonth(date._month, date._year);
	}

	bool isLastDayInMonth() {
		return clsDate::isLastDayInMonth(*this);
	}

	static bool isLastMonthOfYear(short month) {
		return month == 12;
	}

	bool isLastMonthOfYear() {
		return clsDate::isLastMonthOfYear(_month);
	}

	static bool isLastDayOfWeek(clsDate date) {
		return date.getDayOfWeek() == _enDayOfWeek::Sat;
	}

	bool isLastDayOfWeek() {
		return clsDate::isLastDayOfWeek(*this);
	}

	static bool isWeekend(clsDate date) {
		short dayOfWeek = date.getDayOfWeek();
		return dayOfWeek == _enDayOfWeek::Fri || dayOfWeek == _enDayOfWeek::Sat;
	}

	bool isWeekend() {
		return clsDate::isWeekend(*this);
	}

	static bool isBusinessDay(clsDate date) {
		return !date.isWeekend();
	}

	bool isBusinessDay() {
		return clsDate::isBusinessDay(*this);
	}

	static clsDate addOneDay(clsDate date) {
		if (clsDate::isLastDayInMonth(date)) {
			if (clsDate::isLastMonthOfYear(date._month)) {
				date._month = 1;
				date._year++;
			}
			else date._month++;
			date._day = 1;
		}
		else date._day++;
		return date;
	}

	void addOneDay() {
		*this = clsDate::addOneDay(*this);
	}

	static clsDate addDays(clsDate date, short numberOfDays) {
		numberOfDays += clsDate::daysFromStartOfYear(date) - 1;
		date._day = date._month = 1;

		short yearDays;
		while (numberOfDays > (yearDays = date.daysInYear())) {
			date.addOneYear();
			numberOfDays -= yearDays;
		}

		short monthDays;
		while (numberOfDays > (monthDays = clsDate::daysInMonth(date._month, date._year))) {
			if (date._month == 12) {
				date._month = 1;
				date._year++;
			}
			else
				date._month++;
			numberOfDays -= monthDays;
		}
		date._day += numberOfDays;

		return date;
	}

	void addDays(short numberOfDays) {
		*this = clsDate::addDays(*this, numberOfDays);
	}

	static clsDate addOneWeek(clsDate date) {
		return clsDate::addDays(date, 7);
	}

	void addOneWeek() {
		*this = clsDate::addOneWeek(*this);
	}

	static clsDate addWeeks(clsDate date, short numberOfWeeks) {
		date.addDays(numberOfWeeks * 7);
		return date;
	}

	clsDate addWeeks(short numberOfWeeks) {
		return clsDate::addWeeks(*this, numberOfWeeks);
	}

	static clsDate addOneMonth(clsDate date) {
		if (clsDate::isLastMonthOfYear(date._month)) {
			date._month = 1;
			date._year++;
		}
		else date._month++;
		clsDate::_correctDate(date);
		return date;
	}

	void addOneMonth() {
		*this = clsDate::addOneMonth(*this);
	}

	static clsDate addMonths(clsDate date, short numberOfMonths) {
		if (numberOfMonths > 12)
			date.addYears(numberOfMonths / 12);
		numberOfMonths %= 12;

		for (short month = 1; month <= numberOfMonths; month++)
			date.addOneMonth();

		return date;
	}

	void addMonths(short numberOfMonths) {
		*this = clsDate::addMonths(*this, numberOfMonths);
	}

	static clsDate addOneYear(clsDate date) {
		date._year++;
		clsDate::_correctDate(date);
		return date;
	}

	void addOneYear() {
		*this = clsDate::addOneYear(*this);
	}

	static clsDate addYears(clsDate date, short numberOfYears) {
		date.year += numberOfYears;
		clsDate::_correctDate(date);
		return date;
	}

	void addYears(short numberOfYears) {
		*this = clsDate::addYears(*this, numberOfYears);
	}

	static clsDate addOneDecade(clsDate date) {
		date.addYears(10);
		return date;
	}

	void addOneDecade() {
		*this = clsDate::addOneDecade(*this);
	}

	static clsDate addDecades(clsDate date, short numberOfDecades) {
		date.addYears(numberOfDecades * 10);
		return date;
	}

	void addDecades(short numberOfDecades) {
		*this = clsDate::addDecades(*this, numberOfDecades);
	}

	static clsDate addOneCentury(clsDate date) {
		date.addYears(100);
		return date;
	}

	void addOneCentury() {
		*this = clsDate::addOneCentury(*this);
	}

	static clsDate addCenturies(clsDate date, short numberOfCenturies) {
		date.addYears(numberOfCenturies * 100);
		return date;
	}

	void addCenturies(short numberOfCenturies) {
		*this = clsDate::addCenturies(*this, numberOfCenturies);
	}

	static clsDate addOneMillenium(clsDate date) {
		date.addYears(1000);
		return date;
	}

	void addOneMillenium() {
		*this = clsDate::addOneMillenium(*this);
	}

	static clsDate addMilleniums(clsDate date, short numberOfMilleniums) {
		date.addYears(numberOfMilleniums * 1000);
		return date;
	}

	void addMilleniums(short numberOfMilleniums) {
		*this = clsDate::addMilleniums(*this, numberOfMilleniums);
	}

	static clsDate subtractOneDay(clsDate date) {
		if (date._day == 1) {
			if (date._month == 1) {
				date._year--;
				date._month = 12;
			}
			else date._month--;
			date._day = clsDate::daysInMonth(date._month, date._year);
		}
		else date._day--;
		return date;
	}

	void subtractOneDay() {
		*this = clsDate::subtractOneDay(*this);
	}

	static clsDate subtractDays(clsDate date, short numberOfDays) {
		numberOfDays += (date.daysInYear() - date.daysFromStartOfYear());

		date._month = 12;
		date._day = 31;

		short yearDays;
		while (numberOfDays > (yearDays = date.daysInYear())) {
			numberOfDays -= yearDays;
			date.subtractOneYear();
		}

		short monthDays;
		while (numberOfDays > (monthDays = date.daysInMonth(date._month, date._year))) {
			if (date._month == 1) {
				date._month = 12;
				date._year--;
			}
			else date._month--;
			numberOfDays -= monthDays;
		}
		date._day -= numberOfDays;

		return date;
	}

	void subtractDays(short numberOfDays) {
		*this = clsDate::subtractDays(*this, numberOfDays);
	}

	static clsDate subtractOneWeek(clsDate date) {
		date.subtractDays(7);
		return date;
	}

	void subtractOneWeek() {
		clsDate::subtractOneWeek(*this);
	}

	static clsDate subtractWeeks(clsDate date, short numberOfWeeks) {
		date.subtractDays(numberOfWeeks * 7);
		return date;
	}

	void subtractWeeks(short numberOfWeeks) {
		*this = clsDate::subtractWeeks(*this, numberOfWeeks);
	}

	static clsDate subtractOneMonth(clsDate date) {
		if (date._month == 1) {
			date._month = 12;
			date._year--;
		}
		else date._month--;
		clsDate::_correctDate(date);
		return date;
	}

	void subtractOneMonth() {
		*this = clsDate::subtractOneMonth(*this);
	}

	static clsDate subtractMonths(clsDate date, short numberOfMonths) {
		if (numberOfMonths >= 12)
			date.subtractYears(numberOfMonths / 12);
		numberOfMonths %= 12;

		for (short month = 1; month <= numberOfMonths; month++)
			date.subtractOneMonth();
		return date;
	}

	void subtractMonths(short numberOfMonths) {
		*this = clsDate::subtractMonths(*this, numberOfMonths);
	}

	static clsDate subtractOneYear(clsDate date) {
		date._year--;
		clsDate::_correctDate(date);
		return date;
	}

	void subtractOneYear() {
		*this = clsDate::subtractOneYear(*this);
	}

	static clsDate subtractYears(clsDate date, short numberOfYears) {
		date._year -= numberOfYears;
		clsDate::_correctDate(date);
		return date;
	}

	void subtractYears(short numberOfYears) {
		*this = clsDate::subtractYears(*this, numberOfYears);
	}

	static clsDate subtractOneDecade(clsDate date) {
		date.subtractYears(10);
		return date;
	}

	void subtractOneDecade() {
		*this = clsDate::subtractOneDecade(*this);
	}

	static clsDate subtractDecades(clsDate date, short numberOfDecades) {
		date.subtractYears(numberOfDecades * 10);
		return date;
	}

	void subtractDecades(short numberOfDecades) {
		*this = clsDate::subtractDecades(*this, numberOfDecades);
	}

	static clsDate subtractOneCentury(clsDate date) {
		date.subtractYears(100);
		return date;
	}

	void subtractOneCentury() {
		*this = clsDate::subtractOneCentury(*this);
	}

	static clsDate subtractCenturies(clsDate date, short numberOfCenturies) {
		date.subtractYears(numberOfCenturies * 100);
		return date;
	}

	void subtractCenturies(short numberOfCenturies) {
		*this = clsDate::subtractCenturies(*this, numberOfCenturies);
	}

	static clsDate subtractOneMillenium(clsDate date) {
		date.subtractYears(1000);
		return date;
	}

	void subtractOneMillenium() {
		*this = clsDate::subtractOneMillenium(*this);
	}

	static clsDate subtractMilleniums(clsDate date, short numberOfMilleniums) {
		date.subtractYears(numberOfMilleniums * 1000);
		return date;
	}

	void subtractMilleniums(short numberOfMilleniums) {
		*this = clsDate::subtractMilleniums(*this, numberOfMilleniums);
	}

	static short calculateVacationDays(clsDate dateFrom, clsDate dateTo) {
		short vacationDays = 0;
		while (dateFrom.isBefore(dateTo)) {
			if (!dateFrom.isWeekend())
				vacationDays++;
			dateFrom.addOneDay();
		}
		return vacationDays;
	}

	short calculateVacationDays(clsDate dateTo) {
		return clsDate::calculateVacationDays(*this, dateTo);
	}

	static clsDate getVacationReturnDate(clsDate& dateFrom, short vacationDays) {
		clsDate dateTo = dateFrom;
		while (vacationDays > 0) {
			if (!dateTo.isWeekend())
				vacationDays--;
			dateTo.addOneDay();
		}
		return dateTo;
	}

	clsDate getVacationReturnDate(short vacationDays) {
		return clsDate::getVacationReturnDate(*this, vacationDays);
	}

	static short daysDifference(clsDate date1, clsDate date2, bool includeEndDay = false) {
		short signMultiplier = 1;
		if (date2.isBefore(date1)) {
			clsDate::swapDates(date1, date2);
			signMultiplier = -1;
		}

		short numberOfDays = 0;
		numberOfDays = date2.daysFromStartOfYear() - date1.daysFromStartOfYear();
		date1._day = date1._month = 1;

		while (date1._year < date2._year) {
			numberOfDays += date1.daysInYear();
			date1._year++;
		}

		return includeEndDay ? ++numberOfDays * signMultiplier : numberOfDays * signMultiplier;
	}

	short daysDifference(clsDate other, bool includeEndDay = false) {
		return clsDate::daysDifference(*this, other, includeEndDay);
	}

	static bool isValid(clsDate date) {
		if (date._year <= 0)
			return false;
		if (date._month < _enMonth::Jan && date._month > _enMonth::Dec)
			return false;
		if (date._day < 1 || date._day > date.daysInMonth())
			return false;
		return true;
	}

	bool isValid() {
		return clsDate::isValid(*this);
	}

	static clsDate parseDate(string sDate) {
		vector<string> vDate = clsString::split(sDate, "/");
		return clsDate(stoi(vDate[0]), stoi(vDate[1]), stoi(vDate[2]));
	}

	static clsDate getLocalDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return clsDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
	}

	static string getFormattedDate(clsDate date, string dateFormat = "DD/MM/YYYY") {
		string formattedDate = dateFormat;
		formattedDate = clsString::replace(formattedDate, "DD", to_string(date._day));
		formattedDate = clsString::replace(formattedDate, "MM", to_string(date._month));
		formattedDate = clsString::replace(formattedDate, "YYYY", to_string(date._year));
		return formattedDate;
	}

	string getFormattedDate(string dateFormat = "DD/MM/YYYY") {
		return clsDate::getFormattedDate(*this, dateFormat);
	}

	static string getFormattedTime(clsDate date, string timeFormat = "HH:MM:SS") {
		string formattedTime = timeFormat;
		formattedTime = clsString::replace(formattedTime, "HH", to_string(date._hour));
		formattedTime = clsString::replace(formattedTime, "MM", to_string(date._minute));
		formattedTime = clsString::replace(formattedTime, "SS", to_string(date._second));
		return formattedTime;
	}

	string getFormattedTime(string timeFormat = "HH:MM:SS") {
		return clsDate::getFormattedTime(*this, timeFormat);
	}

	static string getFormattedDateAndTime(clsDate date, string delimiter = " - ") {
		return clsDate::getFormattedDate(date) + delimiter + clsDate::getFormattedTime(date);
	}

	string getFormattedDateAndTime(string delimiter = " - ") {
		return clsDate::getFormattedDateAndTime(*this, delimiter);
	}

	void setDay(const short& day) {
		_day = day;
	}

	short getDay() const {
		return _day;
	}

	void setMonth(const short& month) {
		_month = month;
	}

	short getMonth() const {
		return _month;
	}

	void setYear(const short& year) {
		_year = year;
	}

	short getYear() const {
		return _year;
	}

	_declspec(property(get = getDay, put = setDay)) short day;
	_declspec(property(get = getMonth, put = setMonth)) short month;
	_declspec(property(get = getYear, put = setYear)) short year;
};