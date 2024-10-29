#include "UI.h"
#include <iostream>
#include <cstdlib>
#include "TestAll.h"


UI::UI(AdminService& initialAdminService, UserService& initialUserService):
	admin{initialAdminService}, user{initialUserService}
{
}

int UI::chooseMode()
{
	
	std::cout<<"Choose mode:\n";
	std::cout<<"1. Admin\n";
	std::cout<<"2. User\n";
	std::cout << "3. Exit\n";
	return getValidIntInput(1, 3, false);
}

int UI::chooseAdminOption()
{
	printAdminMenu();
	return getValidIntInput(1, 5, false);
}

int UI::chooseUserOption()
{
	printUserMenu();
	return getValidIntInput(1, 4, false);
}

int UI::chooseSavingMode()
{
	std::cout << "In what kind of file do you want to save your events?\n";
	std::cout << "1. HTML file\n";
	std::cout << "2. CSV file\n";
	return getValidIntInput(1,2, false);
}

void UI::addEvent() {
	std::string title = "", description = "", link = "";
	int day, month, year, hour, minute, number_of_participants;
	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::cout << "Description: ";
	std::getline(std::cin, description);
	std::cout << "link: ";
	std::getline(std::cin, link);
	std::cout << "Day: ";
	day = getValidIntInput(1, 31, false);
	std::cout << "Month: ";
	month = getValidIntInput(1, 12, false);
	std::cout << "Year: ";
	year = getValidIntInput(2020, 2030, false);
	std::cout << "Hour: ";
	hour = getValidIntInput(0, 23, false);
	std::cout << "Minute: ";
	minute = getValidIntInput(0,59, false);
	std::cout << "Number of participants: ";
	number_of_participants = getValidIntInput(0, 20000, false);
	bool added;
	try {
		added = this->admin.addEvent(title, description, link, hour, minute, day, month, year, number_of_participants);
	}
	catch (ValidationException& e)
	{
		ValidationExceptionInherited e1{ e.getMessage() };
		std::cout << e1.what();
		added = false;
	}
	if (!added)
		std::cout << "Couldn't add the element to the archive\n";
	else
		std::cout << "Element was successfully added\n";
}

void UI::removeEvent()
{
	std::string title = "";
	int day, month, year;

	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::cout << "Day: ";
	day = getValidIntInput(1,31, false);
	std::cout << "Month: ";
	month = getValidIntInput(1, 12, false);
	std::cout << "Year: ";
	year = getValidIntInput(2024, 2030, false);

	if (this->admin.removeEvent(title, day, month, year))
		std::cout << "Element was successfully removed\n";
	else
		std::cout << "The event is not in the list\n";
}

void UI::updateEvent()
{
	std::string title = "";
	int day, month, year;

	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::cout << "Day: ";
	day = getValidIntInput(1, 31, false);
	std::cout << "Month: ";
	month = getValidIntInput(1, 12, false);
	std::cout << "Year: ";
	year = getValidIntInput(2024, 2030, false);

	std::string new_title = "", new_description = "", new_link = "";
	int new_day, new_month, new_year, new_hour, new_minute, new_number_of_participants;

	std::cout << "Introduce new data: \n";
	new_title = title;
	std::cout << "Description: ";
	std::getline(std::cin, new_description);
	std::cout << "link: ";
	std::getline(std::cin, new_link);
	std::cout << "Day: ";
	new_day = getValidIntInput(1, 31, false);
	std::cout << "Month: ";
	new_month = getValidIntInput(1, 12, false);
	std::cout << "Year: ";
	new_year = getValidIntInput(2024, 2030, false);
	std::cout << "Hour: ";
	new_hour = getValidIntInput(0, 23, false);
	std::cout << "Minute: ";
	new_minute = getValidIntInput(0,59, false);
	std::cout << "Number of participants: ";
	new_number_of_participants = getValidIntInput(0, 20000, false);
	std::cout << "New link: ";
	std::getline(std::cin, new_link);

	if (!this->admin.updateEvent(title, day, month, year, new_title, new_description, new_link, new_hour, new_minute, new_day, new_month, new_year, new_number_of_participants))
		std::cout << "The event does not belong to the list\n";
	else
		std::cout << "Element updated successfully\n";
}

void UI::displayAll()
{
	int number_of_events = this->admin.getRepository().size();
	for (int i = 0; i < number_of_events; i++) {
		Event event = this->admin.getRepository()[i];
		std::cout << event.toString();
		std::cout << '\n';
	}
}

void UI::start()
{
	int mode = chooseMode();
	while (true) {
		if (mode == 1)
		{
			std::cout << "You are in ADMIN mode\n";
			while (mode == 1)
			{
				int option;
				option = chooseAdminOption();
				if (option == 1)
					addEvent();
				else if (option == 2)
					removeEvent();
				else if (option == 3)
					updateEvent();
				else if (option == 4)
					displayAll();
				else if (option == 5)
				{
					mode = 4;// choose mode
				}
			}
		}
		else if (mode == 2)
		{				
			std::cout << "You are in USER mode\n";
			this->user.updateUserRepository();
			while (mode == 2)
			{
				int option;
				option = chooseUserOption();
				if (option == 1)
					optionSeeEventsForGivenMonth();
				else if (option == 2)
					optionSeeYourFutureEvents();
				else if (option == 3)
					optionOpenWishlist();
				else
					mode = 4;// choose mode
			}

		}
		else if (mode == 3)
			break;
		else if (mode == 4) {
			mode = chooseMode();
		}
	}
}

void UI::printAdminMenu()
{
	std::cout << "Choose action: \n";
	std::cout << "1. Add event\n";
	std::cout << "2. Remove event\n";
	std::cout << "3. Update event\n";
	std::cout << "4. Display all events\n";
	std::cout << "5. Exit admin mode\n";
}

void UI::printUserMenu()
{
	std::cout << "Choose action: \n";
	std::cout << "1. See events for specified month\n";
	std::cout << "2. See your future events\n";
	std::cout << "3. Open the list of events in wanted format\n";
	std::cout << "4. Exit user mode\n";
}

void UI::optionSeeEventsForGivenMonth()
{
	int month;
	std::cout << "For what month do you want to see the events?\n";
	month = getValidIntInput(1, 12, true);
	int v[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	if (month == -24329)
		for (int i = 1; i <= 12; i++)
			seeEventsForMonth(i);
	else
	{
		while (month)
		{
			seeEventsForMonth(month);
			std::cout << "Do you want to see events for next month?\n1. Yes\n2. No\n";
			int choice;
			choice = getValidIntInput(1, 2, false);
			if (choice == 1)
			{
				if (month == 12)
					month = 1;
				else month = month + 1;
			}
			else
				month = 0;
		}
	}
}

void UI::optionSeeYourFutureEvents()
{
	int number_of_events = this->user.getWishlist().size();
	for (int i = 0; i < number_of_events; i++) {
		Event event = this->user.getWishlist()[i];
		std::string command = "start " + event.getLink();
		system(command.c_str());
		std::cout << event.toString();
		std::cout << '\n';
		std::cout << "Do you want to keep this event in the list?\n1. Yes\n2. No\n3. Exit\n";
		int option = getValidIntInput(1, 3, false);
		if (option == 2)
		{
			user.removeEventFromWishlist(event, i);
			i -= 1;
			number_of_events -= 1;
		}
		if (option == 3)
			i = number_of_events + 1;
	}

}

void UI::seeEventsForMonth(int month)
{
	Repository events{ user.getEventsForGivenMonth(month) };
	for (int i = 0; i < events.getSize(); i++)
	{
		Event event = events.getRepository()[i];
		std::string command = "start " + event.getLink();
		system(command.c_str());
		std::cout << event.toString();
		std::cout << '\n';
		std::cout << "Do you want to add this event to your list? \n1. Yes\n2. No\n3. Exit\n";

		int addToList = getValidIntInput(1, 3, false);
		if (addToList == 1)
			user.addEventToWishlist(event, i);
		if (addToList == 3)
			i = events.getSize() + 1;
	}
}


int UI::getValidIntInput(int min, int max, bool allowEmpty = false)
{
	while (true) {
		std::string option;		
		std::getline(std::cin, option);
		if (option == "" && allowEmpty)
			return -24329;
	
		int optionInt;
		try
		{
			optionInt = std::stoi(option);
			if (optionInt > max || optionInt < min)
				throw std::invalid_argument("");
			return optionInt;
		}
		catch (std::invalid_argument) {
			std::cout << "Introduce a valid value\n";
		}
		catch (std::out_of_range) {
			std::cout << "Introduce a valid value\n";
		}
	}
}

void UI::optionOpenWishlist()
{
	int fileType = chooseSavingMode();
	if (fileType == 1)
	{
		Repository wishlist(this->user.getWishes());
		wishlist.saveAsHTML("wishlist.html");
	}
	else {
		Repository wishlist(this->user.getWishes());
		wishlist.saveAsCSV("wishlist.csv");
	}
}
