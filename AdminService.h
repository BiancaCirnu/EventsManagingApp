#pragma once
#include "Repository.h"
class AdminService
{
private:
	Repository repository;
public:
	AdminService(Repository initialRepo);
	bool addEvent(std::string title, std::string description, std::string link, int hour, int minute, int day, int month, int year, int nr_of_participants);
	bool removeEvent(std::string title, int day, int month, int year);
	bool updateEvent(std::string title, int day, int month, int year, std::string new_title, std::string new_description, std::string new_link, int new_hour, int new_minute, int new_day, int new_month, int new_year, int new_nr_of_participants);
	std::vector<Event> getRepository();
	void initialzeRepository();
	Repository getRepo();
};

