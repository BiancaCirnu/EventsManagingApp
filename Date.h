#pragma once
#include <string>

class Date
{
private:
	int day, month, year;
public:
	Date(int day=1,int month=1,int year = 2000);
	void operator=(const Date& date);

	int getDay();
	int getMonth();
	int getYear();

	bool operator==(const Date& date_to_compare);
	std::string toString();
	bool operator<(const Date& date_to_compare);
	bool operator>(const Date& date_to_compare);
};
