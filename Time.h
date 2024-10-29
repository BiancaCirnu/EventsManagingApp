#pragma once
#include <string>
class Time
{
private:
	int hour, minute;
public:
	Time(int hour=0, int minute=0);
	void operator=(const Time& time);
	int getHour();
	int getMinute();
	std::string toString();
};

