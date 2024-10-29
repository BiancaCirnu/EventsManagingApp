#pragma once
#include "Repository.h"
#include "DynamicArray.h"
class UserService
{
private:
	Repository repository;
	Repository wishlist;
public:
	UserService(Repository initialRepo, Repository wishlist);
	Repository getRepo();
	void updateUserRepository();
	Repository getEventsForGivenMonth(int month);
	Repository getAllEvents();
	void addEventToWishlist(Event event, int eventIndex);
	void removeEventFromWishlist(Event event, int eventIndex);
	std::vector<Event> getWishlist();
	Repository getWishes();
};

