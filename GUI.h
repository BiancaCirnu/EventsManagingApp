#pragma once
#include <qobject.h>
#include "../LifeAfterSchool/AdminService.h"
#include "../LifeAfterSchool/UserService.h"


class GUI: public QObject
{
	Q_OBJECT
private:
	AdminService adm;
	UserService usr;
	int argumentCount;
	char** argumentVector;

public:
	GUI(AdminService a, UserService u, int initialArgumentCount, char** initialArgumentVector) : adm{ a }, usr{ u }, argumentCount{ initialArgumentCount }, argumentVector{ initialArgumentVector } {};
	
	int start();

	// admin functions
	int newEvent();
	int updateEvent(int i);
	int seeAllEvents();

	// user functions
	int wishlist();
	int seeEventsForMonthMenu();
	int seeEvents(int i);

	int adminGUI();
	int userGUI();
};

