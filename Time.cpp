#include "Time.h"
#include <string>
#include <iostream>

Time::Time(int hour,int minute)
{
	this->hour = hour;
	this->minute = minute;
}

void Time::operator=(const Time& time)
{
	this->hour = time.hour;
	this->minute = time.minute;
}

int Time::getHour()
{
	return this->hour;
}

int Time::getMinute()
{
	return this->minute;
}

std::string Time::toString()
{
	std::string time;
	if (this->hour < 10)
		time = "0" + std::to_string(getHour()) + ":";
	else
		time = std::to_string(getHour()) + ":";
	if (this->minute < 10)
		time += "0" + std::to_string(getMinute());
	else
		time += std::to_string(getMinute());
	return time;
}


