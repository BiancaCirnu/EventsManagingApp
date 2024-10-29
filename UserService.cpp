#include "UserService.h"

UserService::UserService(Repository initial_repository, Repository wishlist) : repository{ initial_repository}, wishlist{ wishlist }
{
}

Repository UserService::getRepo()
{
	return this->repository;
}

void UserService::updateUserRepository()
{
	this->repository.readFromFile();
}

Repository UserService::getEventsForGivenMonth(int month)
{
	std::vector<Event> emptyVector;
	Repository repo{"empty.txt", emptyVector};
	for (auto ev : this->repository.getRepository())
		if (ev.getDate().getMonth() == month)
			repo.addEvent(ev);
	repo.sortEvents();
	return repo;
}

Repository UserService::getAllEvents()
{
	std::vector<Event> emptyVector;
	Repository repo{ "empty.txt", emptyVector };
	for (auto ev : this->repository.getRepository())
		repo.addEvent(ev);
	repo.sortEvents();
	return repo;
}

void UserService::addEventToWishlist(Event event, int eventIndex)
{
	int new_nr = event.getNrOfParticipants() + 1;
	event.setNrOfParticipants(new_nr);
	repository.getRepository()[eventIndex] =  event;
	this->wishlist.addEvent(event);
	this->repository.writeToFile();
	this->wishlist.writeToFile();
}

void UserService::removeEventFromWishlist(Event event, int eventIndex)
{
	int new_nr = event.getNrOfParticipants() - 1;
	event.setNrOfParticipants(new_nr);
	repository.getRepository()[eventIndex] = event;
	this->wishlist.removeEvent(eventIndex);
	this->wishlist.writeToFile();
}

std::vector<Event> UserService::getWishlist()
{
	return this->wishlist.getRepository();
}

Repository UserService::getWishes() {
	return this->wishlist;
}