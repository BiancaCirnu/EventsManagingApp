#pragma once
#include<string>
#include "Date.h"
#include "Time.h"

class Event
{
private:
	std::string title;
	std::string description;
	Date date;
	Time time;
	int number_of_participants;
	std::string link;

public:
	Event(std::string title = "", std::string description = "", Date date = Date{},
		Time time = Time{}, int number_of_participants = 0, std::string link = "");
	//getters
	std::string getTitle();
	std::string getDescription();
	Date getDate();
	Time getTime();
	int getNrOfParticipants();
	std::string getLink();

	//setters
	void setTitle(std::string new_title);
	void setDescription(std::string new_description);
	void setDate(Date new_date);
	void setTime(Time new_time);
	void setNrOfParticipants(int new_number);
	void setLink(std::string new_link);

	bool operator==(const Event& event_to_compare);
	void operator=(const Event& event_to_copy);

	bool isEqual(std::string title, int day, int month, int year);
	std::string toString();

	friend std::istream& operator>>(std::istream& inputFile, Event& event);
	friend std::ostream& operator<<(std::ostream& outputFile, const Event& event);

};

