#include "repository.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
Repository::Repository() {};
Repository::Repository(std::string filename, std::vector<Event> initialEvents): repository{ initialEvents }, filename{filename}
{
	if (filename!="empty.txt")
		readFromFile();
}

std::vector<Event> Repository::getRepository() {
	return this->repository;
}

bool Repository::addEvent(Event new_event)
{
	EventValidator validator;
	validator.validate(new_event);
	if (this->getEventPosition(new_event) != -1)
		return false;
	this->repository.push_back(new_event);
	return true;
}

bool Repository::removeEvent(int event_index)
{
	if (this->repository.size() > event_index || event_index < 0)
	{
		this->repository.erase(this->repository.begin() + event_index, this->repository.begin() + event_index+1);
		return true;
	}
	return false;
}

bool Repository::updateEvent(int event_index, Event modified_event)
{
	if (this->repository.size() >= event_index || event_index < 0) {
		this->repository.emplace(this->repository.begin() + event_index, modified_event);
		return true;
	}
	return false;
}

int Repository::getEventPosition(Event event)
{
	auto it = std::find(this->repository.begin(), this->repository.end(), event);
	if (it != this->repository.end())
		return std::distance(this->repository.begin(), it);
	else
		return -1;
}

int Repository::getSize()
{
	return this->repository.size();
}

void Repository::operator=(Repository& repository)
{
	this->repository = repository.repository;
}


void Repository::sortEvents()
{
	struct
	{
		bool operator()(Event a, Event b) const { return a.getDate() < b.getDate(); }
	}
	customLess;
	std::sort(this->repository.begin(), this->repository.end(), customLess);
}

void Repository::saveAsHTML(std::string filename)
{
	std::ofstream outputHTML(filename);
	if (!outputHTML.is_open())
		throw std::exception("Couldn't open the file.");
	outputHTML << "<!DOCTYPE html>\n";
	outputHTML << "<html>\n";
	outputHTML << "<style>\n";
	outputHTML << "table, th, td {\nborder:1px solid black;\n}\n";
	outputHTML << "</style>\n";
	outputHTML << "<body>\n";

	outputHTML << "<table style>\n";
	outputHTML << " <tr>\n";
	outputHTML << "  <th>Title</th>\n";
	outputHTML << "  <th>Description</th>\n";
	outputHTML << "  <th>Date</th>\n";
	outputHTML << "  <th>Time</th>\n";
	outputHTML << "  <th>Number of participants</th>\n";
	outputHTML << "  <th>Link</th>\n";
	outputHTML << " </tr>\n";
	std::vector<Event> copyRepo = getRepository();
	for (auto ev: copyRepo)
	{
		outputHTML << " <tr>\n";
		outputHTML << "  <td>"<<ev.getTitle()<<"</td>\n";
		outputHTML << "  <td>" << ev.getDescription() << "</td>\n";
		outputHTML << "  <td>" << ev.getDate().toString() << "</td>\n";
		outputHTML << "  <td>" << ev.getTime().toString() << "</td>\n";
		outputHTML << "  <td>" << ev.getNrOfParticipants() << "</td>\n";
		outputHTML << "  <td><a href = " << ev.getLink() << "> Link </td>\n";
		outputHTML << " </tr>\n";

	}
	outputHTML << "</body>\n";
	outputHTML << "</html>\n";
	outputHTML.close();
	std::string tostr = "start " + filename;
	system(tostr.c_str());
}

void Repository::saveAsCSV(std::string filename)
{
	std::ofstream outputCSV(filename);
	if (!outputCSV.is_open())
		throw std::exception("Couldn't open the file");
	int i = 0;
	for (auto ev : this->repository) {
		i++;
		outputCSV << i << ", " << ev.getTitle() << ", " << ev.getDescription() << ", " << ev.getDate().toString() << ", "
			<< ev.getTime().toString() << ", " << ev.getNrOfParticipants() << ", " << ev.getLink()<<'\n';
	}
	outputCSV.close();

	std::string tostr = "start " + filename;
	system(tostr.c_str());
}

void Repository::readFromFile()
{
	std::ifstream inputFile(this->filename);
	if (!inputFile.is_open())
		throw std::exception();

	std::vector<Event> repo;
	Event event;
	while (inputFile >> event) {
		std::string buffer;
		repo.push_back(event);
		std::getline(inputFile, buffer);
	}
	this->repository = repo;
	inputFile.close();

}


void Repository::writeToFile()
{
	std::ofstream outputFile(this->filename, std::ofstream::trunc);
	if (!outputFile.is_open())
		return;
	for (auto event : this->repository)
	{
		outputFile << event <<'\n';
	}
	outputFile.close();
}

