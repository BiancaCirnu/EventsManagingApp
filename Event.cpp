#include "Event.h"
#include <iostream>
#include <vector>
#include<sstream>

std::vector<std::string> split_string(std::string initialString, char delimiter) {
	std::stringstream ss(initialString);
	std::vector<std::string> tokens;
	while (!ss.eof())
	{
		std::string newWord;
		std::getline(ss, newWord, delimiter);
		tokens.push_back(newWord);
	}
	return tokens;
}

//get rid of spaces at the end and at the beginning of the string
std::string strip_string(const std::string& initialString) {
	std::string s(initialString);
	s.erase(0, s.find_first_not_of(" \n"));
	s.erase(s.find_last_not_of(" \n") + 1);
	return s;

}

std::vector<int> readDate(std::string date)
{
	date = strip_string(date);
	std::vector<std::string> day_month_year = split_string(date, ' ');
	int day = std::stoi(day_month_year[0]);
	int month;
	if (day_month_year[1] == "January")
		month = 1;
	else if (day_month_year[1] == "February")
		month = 2;
	else if (day_month_year[1] == "March")
		month = 3;
	else if (day_month_year[1] == "April")
		month = 4;
	else if (day_month_year[1] == "May")
		month = 5;
	else if (day_month_year[1] == "June")
		month = 6;
	else if (day_month_year[1] == "July")
		month = 7;
	else if (day_month_year[1] == "August")
		month = 8;
	else if (day_month_year[1] == "September")
		month = 9;
	else if (day_month_year[1] == "October")
		month = 10;
	else if (day_month_year[1] == "November")
		month = 11;
	else if (day_month_year[1] == "December")
		month = 12;
	int year = std::stoi(day_month_year[2]);
	std::vector<int> dateVec;
	dateVec.push_back(day);
	dateVec.push_back(month);
	dateVec.push_back(year);
	return dateVec;
}
Event::Event(std::string title , std::string description , Date date,
	Time time, int number_of_participants, std::string link)
{
	this->title = title;
	this->description = description;
	this->date = date;
	this->time = time;
	this->number_of_participants = number_of_participants;
	this->link = link;
}

std::string Event::getTitle()
{
	return this->title;
}

std::string Event::getDescription()
{
	return this->description;
}

Date Event::getDate() 
{
	return this->date;
}

Time Event::getTime()
{
	return this->time;
}

int Event::getNrOfParticipants()
{
	return this->number_of_participants;
}

std::string Event::getLink()
{
	return this->link;
}

void Event::setTitle(std::string new_title) {
	this->title = new_title;
}

void Event::setDescription(std::string new_descriprion) {
	this->description = new_descriprion;
}

void Event::setNrOfParticipants(int new_number)
{
	this->number_of_participants = new_number;
}

bool Event::operator==(const Event& event_to_compare)
{
	if (this->title == event_to_compare.title && this->date == event_to_compare.date)
		return true;
	return false;
}

void Event::operator=(const Event& event_to_copy)
{
	this->title = event_to_copy.title;
	this->description = event_to_copy.description;
	this->date = event_to_copy.date;
	this->time = event_to_copy.time;
	this->number_of_participants = event_to_copy.number_of_participants;
	this->link = event_to_copy.link;
}

bool Event:: isEqual(std::string title, int day, int month, int year)
{
	Date date{ day,month, year };
	if (date == this->date && title == this->title)
		return true;
	return false;
}

std::string Event::toString()
{
	std::string event;
	event = "Title: " + getTitle() + "\nDescription: " + getDescription() + "\nDate: " + getDate().toString() + "\nTime: " + getTime().toString()+ "\nNumber of participants: " + std::to_string(getNrOfParticipants()) + "\nLink: " + getLink() + '\n';
	return event;

}


void Event::setDate(Date new_date) {
	this->date = new_date;
}

void Event::setTime(Time new_time) {
	this->time = new_time;
}

void Event::setLink(std::string new_link) {
	this->link = new_link;
}



std::istream& operator>>(std::istream& inputFile, Event& event) {

	std::string line;
	getline(inputFile, line);
	if (line == "")
		return inputFile;
	std::string title = split_string(line, ':')[1];
	title = strip_string(title);

	getline(inputFile, line);
	std::string description = split_string(line, ':')[1];
	description = strip_string(description);

	getline(inputFile, line);
	std::string date = split_string(line, ':')[1];	
	date = strip_string(date);
	std::vector<std::string> day_month_year = split_string(date, ' ');
	int day = std::stoi(day_month_year[0]);
	int month;
	if (day_month_year[1] == "January")
		month = 1;
	else if (day_month_year[1] == "February")
		month = 2;
	else if (day_month_year[1] == "March")
		month = 3;
	else if (day_month_year[1] == "April")
		month = 4;
	else if (day_month_year[1] == "May")
		month = 5;
	else if (day_month_year[1] == "June")
		month = 6; 
	else if (day_month_year[1] == "July")
		month = 7;
	else if (day_month_year[1] == "August")
		month = 8; 
	else if (day_month_year[1] == "September")
		month = 9;
	else if (day_month_year[1] == "October")
		month = 10;
	else if (day_month_year[1] == "November")
		month = 11;
	else if (day_month_year[1] == "December")
		month = 12;
	int year = std::stoi(day_month_year[2]);

	getline(inputFile, line);
	std::string hour_str = split_string(line, ':')[1];
	hour_str = strip_string(hour_str);
	std::string minute_str = split_string(line, ':')[2];
	int hour = std::stoi(hour_str);
	int minute = std::stoi(minute_str);

	getline(inputFile, line);
	std::string participants = split_string(line, ':')[1];
	participants = strip_string(participants);
	int participants_int = std::stoi(participants);
	
	getline(inputFile, line);	
	std::vector<std::string> linkVector = split_string(line, ':');
	linkVector[1] = strip_string(linkVector[1]);
	std::string linkString;
	for (auto link : linkVector)
		if (link == linkVector[1])
			linkString = link;
		else if (link != linkVector[0])
			linkString = linkString + ":" + link;
	Time evTime{ hour, minute };
	Date evDate{ day, month, year };
	event = Event(title, description, evDate, evTime, participants_int, linkString);
	return inputFile;
}

std::ostream& operator<<(std::ostream& outputFile, const Event& event) {
	Event ev = event;
	outputFile << ev.toString();
	return outputFile;
}