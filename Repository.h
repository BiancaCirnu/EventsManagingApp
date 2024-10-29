#pragma once
#include "Event.h"
#include <vector>
#include <algorithm>
#include<fstream>
#include "Validator.h"
class Repository
{
private:
	std::vector<Event> repository;
	std::string filename;
	Repository();

public:
	Repository(std::string filename, std::vector<Event> initialEvents);
	std::vector<Event> getRepository();
	bool addEvent(Event new_event);
	bool removeEvent(int event_index);
	bool updateEvent(int event_index, Event modified_event);
	int getEventPosition(Event event);
	int getSize();
	void operator=(Repository& repository);
	void sortEvents();
	
	void saveAsHTML(std::string filename);
	void saveAsCSV(std::string filename);
	void readFromFile();
	void writeToFile();

};

