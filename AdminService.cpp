#include "AdminService.h"
#include <iostream>

AdminService::AdminService(Repository initialRepo): repository{initialRepo}
{
}

bool AdminService::addEvent(std::string title, std::string description, std::string link, int hour, int minute, int day, int month, int year, int nr_of_participants)
{
	Date date{ day, month, year };
	Time time{ hour, minute };
	Event new_event{ title, description, date, time, nr_of_participants, link };
	for (auto ev: this->repository.getRepository())
		if (new_event == ev)
			return false;
	if (!this->repository.addEvent(new_event))
		return false;
	
	this->repository.writeToFile();

	return true;
}

bool AdminService::removeEvent(std::string title, int day, int month, int year)
{
	int i= -1;
	int elementIndex = -1;
	for (auto ev : this->repository.getRepository()) {
		i++;
		if (ev.isEqual(title, day, month, year))
			elementIndex = i;
	}
	if (elementIndex>=0) {
		this->repository.removeEvent(elementIndex);
		this->repository.writeToFile();

		return true;
	}
	return false;
}

bool AdminService::updateEvent(std::string title, int day, int month, int year, std::string new_title, std::string new_description, std::string new_link, int new_hour, int new_minute, int new_day, int new_month, int new_year, int new_nr_of_participants)
{
	int i = 0, elementIndex=-1;
	for (auto ev : this->repository.getRepository())
	{
		if (ev.isEqual(title, day, month, year))
			elementIndex = i;
		i++;
	}
	if (elementIndex == -1)
		return false;
	Date new_date{ new_day, new_month, new_year };
	Time new_time{ new_hour, new_minute };
	Event new_event{ new_title, new_description, new_date, new_time, new_nr_of_participants, new_link };
	this->repository.removeEvent(elementIndex);
	this->repository.updateEvent(elementIndex, new_event);
	this->repository.writeToFile();


}

std::vector<Event> AdminService::getRepository()
{
	return this->repository.getRepository();
}

void AdminService::initialzeRepository()
{
	addEvent("Coma", "/Form", "https://www.facebook.com/events/1827184704467073", 20, 30, 6, 4, 2024, 63);
	addEvent("Pinholes", "/Form", "https://www.facebook.com/events/1197524461217256", 20, 30, 5, 4, 2024, 32);
	addEvent("Trooper", "Hardward", "https://www.facebook.com/events/3519763628291223", 20, 0, 20, 4, 2024, 30);
	addEvent("Truda", "Hardward", "https://www.facebook.com/events/7973241402702597", 20, 0, 26, 4, 2024, 21);
	addEvent("Celelalte Cuvinte", "Hardward", "https://www.facebook.com/events/3675191309467653", 21, 0, 18, 5, 2024, 27);
	addEvent("Coma", "/Form", "https://www.facebook.com/events/1827184704467073", 20, 30, 6, 4, 2024, 63);
	addEvent("Luna amara", "Zazen", "https://www.facebook.com/events/754522162971481", 20, 30, 12, 4, 2024, 93);
	addEvent("Dirty Shirt", "Zazen", "https://www.facebook.com/events/754522162971481", 21, 30, 12, 4, 2024, 94);
	addEvent("Implant pentru refuz", "Zazen", "https://www.facebook.com/events/754522162971481", 20, 30, 13, 4, 2024, 93);
	addEvent("Dirty Shirt", "Zazen", "https://www.facebook.com/events/754522162971481", 21, 30, 13, 4, 2024, 94);
}

Repository AdminService::getRepo()
{
	this->repository.readFromFile();
	return this->repository;
}
