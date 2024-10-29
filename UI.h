#pragma once
#include "AdminService.h"
#include "UserService.h"
class UI
{
private:
	AdminService admin;
	UserService user;
public:
	UI(AdminService& initialAdminService, UserService& initialUserService);
	void start();
	int chooseMode();
	int chooseAdminOption();
	int chooseUserOption();
	int chooseSavingMode();
	int getValidIntInput(int min, int max, bool allowEmpty);


	void addEvent();
	void removeEvent();
	void updateEvent();
	void displayAll();
	void printAdminMenu();

	void printUserMenu();
	void optionSeeEventsForGivenMonth();
	void optionSeeYourFutureEvents();
	void seeEventsForMonth(int month);
	void optionOpenWishlist();
};
;
