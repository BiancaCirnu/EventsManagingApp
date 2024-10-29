#include "Date.h"
#include<iostream>
#include <vector>
Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

void Date::operator=(const Date& date)
{
	this->day = date.day;
	this->month = date.month;
	this->year = date.year;
}

int Date::getDay()
{
	return this->day;
}

int Date::getMonth()
{
	return this->month;
}

int Date::getYear()
{
	return this->year;
}



bool Date::operator==(const Date& date_to_compare)
{
	if (this->day == date_to_compare.day && this->month == date_to_compare.month && this->year == date_to_compare.year)
		return true;
	return false;
}

std::string Date::toString()
{
	std::string month;
	if (this->month == 1)
		month = "January";
	else if (this->month == 2)
		month = "February";
	else if (this->month == 3)
		month = "March";
	else if (this->month == 4)
		month = "April";
	else if (this->month == 5)
		month = "May";
	else if (this->month == 6)
		month = "June";
	else if (this->month == 7)
		month = "July";
	else if (this->month == 8)
		month = "August";
	else if (this->month == 9)
		month = "September";
	else if (this->month == 10)
		month = "October";
	else if (this->month == 11)
		month = "November";
	else if (this->month == 12)
		month = "December";
	std::string date = std::to_string(this->day) + " " + month + " " + std::to_string(this->year);
	return date;
}

bool Date::operator<(const Date& date_to_compare)
{
	std::string day, month;
	std::string date1 = std::to_string(this->getYear()) + '.';

	if (this->getMonth() < 10)
		date1 += '0';
	date1 += std::to_string(this->getMonth()) + '.';

	if (this->getDay() < 10)
		date1 += '0';
	date1 += std::to_string(this->getDay());

	std::string date2 = std::to_string(date_to_compare.year) + '.';
	if (date_to_compare.month < 10)
		date2 += '0';
	date2 += std::to_string(date_to_compare.month) + '.';

	if (date_to_compare.day < 10)
		date2 += '0';
	date2 += std::to_string(date_to_compare.day);
	return date1 < date2;
}

bool Date::operator>(const Date& date_to_compare)
{
	return !(*this < date_to_compare) && !(*this == date_to_compare);
}

