#include "GUI.h"
#include <qwidget.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qdialog.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <sstream>
#include <vector>
#include <qdatetimeedit.h>
#include <QDate>


int GUI::start()
{
    QApplication app(this->argumentCount, this->argumentVector);

    QWidget mainWindow{};
    mainWindow.setStyleSheet("background-color: #FEDE8F; color: #856518");
    mainWindow.setWindowTitle("Events");
	QLabel* title = new QLabel("Events App");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 30px; font-weight: bold; margin-bottom: 20px;");

	QVBoxLayout* main = new  QVBoxLayout{};
	QVBoxLayout* buttons = new  QVBoxLayout{};

	QPushButton* adminButton = new QPushButton{};
	QPushButton* userButton = new QPushButton{};

	adminButton->setText("Start application as admin");
	adminButton->setStyleSheet("color: #FEDE8F; background-color: #856518");
	buttons->addWidget(adminButton);

	userButton->setText("Start application as user");
	userButton->setStyleSheet("color: #FEDE8F; background-color: #856518");
	buttons->addWidget(userButton);

	QObject::connect(adminButton, &QPushButton::clicked, this, &GUI::adminGUI);
	QObject::connect(userButton, &QPushButton::clicked, this, &GUI::userGUI);

	main->addWidget(title);
	main->addLayout(buttons);

	mainWindow.setLayout(main);
	mainWindow.resize(500, 250);
	mainWindow.show();
	return app.exec();
}

int GUI::wishlist()
{

	QDialog* user = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	user->setLayout(mainLayout);

	QLabel* title = new QLabel("Events");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QTableWidget* table = new QTableWidget();
	table->setRowCount(usr.getWishlist().size());
	table->setColumnCount(7);
	table->setStyleSheet("background-color: #FEDE8F; color: #856518; font-size: 16px; font-weight: bold");

	QStringList header;
	header.append("Title");
	header.append("Description");
	header.append("Date");
	header.append("Time");
	header.append("Participants");
	header.append("Link");
	header.append("Remove");
	table->setHorizontalHeaderLabels(header);
	int rowNr = 0;
	std::vector<QPushButton*> removeButtons;
	std::vector<QPushButton*> openEvents;
	std::vector<Event> events = usr.getWishlist();
	for (auto ev : events)
	{
		QTableWidgetItem* t = new QTableWidgetItem{ ev.getTitle().c_str() };
		t->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* description = new QTableWidgetItem{ ev.getDescription().c_str() };
		description->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* date = new QTableWidgetItem{ ev.getDate().toString().c_str() };
		date->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* time = new QTableWidgetItem{ ev.getTime().toString().c_str() };
		time->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* participants = new QTableWidgetItem{ std::to_string(ev.getNrOfParticipants()).c_str() };
		participants->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* link = new QTableWidgetItem{ ev.getLink().c_str() };
		link->setTextAlignment(Qt::AlignCenter);

		QPushButton* removeButton = new QPushButton{ "X" };
		removeButton->setStyleSheet("font-family: Verdana; font-size: 16px; font-weight: bold; color: #f70808; ");
		removeButtons.push_back(removeButton);
		
		QPushButton* openEvent = new QPushButton{ "Open" };
		openEvent->setStyleSheet("font-family: Verdana;font - size: 14px; font-weight: bold; color: #F78AFF;");
		openEvents.push_back(openEvent);

		table->setItem(rowNr, 0, t);
		table->setItem(rowNr, 1, description);
		table->setItem(rowNr, 2, date);
		table->setItem(rowNr, 3, time);
		table->setItem(rowNr, 4, participants);
		table->setCellWidget(rowNr, 5, openEvent);
		table->setCellWidget(rowNr, 6, removeButton);

		rowNr++;
	}
	table->resizeColumnsToContents();
	for (int i = 0; i < events.size(); i++)
	{
		QObject::connect(removeButtons[i], &QPushButton::clicked, this, [&, i]() {
			usr.removeEventFromWishlist(events[i], i);
			user->hide();
			wishlist();
			});
	}
	mainLayout->addWidget(title);
	mainLayout->addWidget(table);

	user->showMaximized();
	return user->exec();
}

int GUI::seeEventsForMonthMenu()
{
	QDialog* user = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	user->setLayout(mainLayout);

	QLabel* title = new QLabel("Choose month");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	std::vector<QPushButton*> months;
	QVBoxLayout* buttons = new  QVBoxLayout{};

	QPushButton* seeAll = new QPushButton{};
	seeAll->setText("SEE ALL EVENTS FROM THE LIST");
	seeAll->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(seeAll);

	QPushButton* january = new QPushButton{};
	january->setText("January");
	january->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(january);

	QPushButton* february = new QPushButton{};
	february->setText("February");
	february->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(february);

	QPushButton* march = new QPushButton{};
	march->setText("March");
	march->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(march);

	QPushButton* april = new QPushButton{};
	april->setText("April");
	april->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(april);

	QPushButton* may = new QPushButton{};
	may->setText("May");
	may->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(may);

	QPushButton* june = new QPushButton{};
	june->setText("June");
	june->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(june);

	QPushButton* july = new QPushButton{};
	july->setText("July");
	july->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(july);
	
	QPushButton* august = new QPushButton{};
	august->setText("August");
	august->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(august);

	QPushButton* september = new QPushButton{};
	september->setText("September");
	september->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(september);

	QPushButton* october = new QPushButton{};
	october->setText("October");
	october->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(october);

	QPushButton* november = new QPushButton{};
	november->setText("November");
	november->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(november);

	QPushButton* december = new QPushButton{};
	december->setText("December");
	december->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	months.push_back(december);

	for (int i = 0; i < 13; i++)
	{
		QObject::connect(months[i], &QPushButton::clicked, this, [&, i]() {
		seeEvents(i);
			});
		
		buttons->addWidget(months[i]);
	}
	mainLayout->addWidget(title);
	mainLayout->addLayout(buttons);

	user->setLayout(mainLayout);
	user->baseSize();
	user->show();
	return user->exec();
}

int GUI::seeEvents(int i)
{
	QDialog* user = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();

	QHBoxLayout* buttons = new QHBoxLayout();
	user->setLayout(mainLayout);

	QLabel* title = new QLabel();
	if (i == 0)
		title->setText("All events");
	else if (i == 1)
		title->setText("January");
	else if (i == 2)
		title->setText("February");
	else if (i == 3)
		title->setText("March");
	else if (i == 4)
		title->setText("April");
	else if (i == 5)
		title->setText("May");
	else if (i == 6)
		title->setText("June");
	else if (i == 7)
		title->setText("July");
	else if (i == 8)
		title->setText("August");
	else if (i == 9)
		title->setText("September");
	else if (i == 10)
		title->setText("October");
	else if (i == 11)
		title->setText("November");
	else if (i == 12)
		title->setText("December");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");
	std::vector<Event> vec;
	if (i == 0)
		vec = usr.getAllEvents().getRepository();
	else
		vec = usr.getEventsForGivenMonth(i).getRepository();

	QTableWidget* table = new QTableWidget();
	table->setRowCount(vec.size());
	table->setColumnCount(7);
	table->setStyleSheet("background-color: #FEDE8F; color: #856518; font-size: 16px; font-weight: bold");

	QStringList header;
	header.append("Title");
	header.append("Description");
	header.append("Date");
	header.append("Time");
	header.append("Participants");
	header.append("Link");
	header.append("Add to your events");

	table->setHorizontalHeaderLabels(header);
	int rowNr = 0;
	std::vector<QPushButton*> addWishlist;
	std::vector<QPushButton*> openEvents;
	std::vector<Event> events = vec;
	for (auto ev : events)
	{
		QTableWidgetItem* t = new QTableWidgetItem{ ev.getTitle().c_str() };
		t->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* description = new QTableWidgetItem{ ev.getDescription().c_str() };
		description->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* date = new QTableWidgetItem{ ev.getDate().toString().c_str() };
		date->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* time = new QTableWidgetItem{ ev.getTime().toString().c_str() };
		time->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* participants = new QTableWidgetItem{ std::to_string(ev.getNrOfParticipants()).c_str() };
		participants->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* link = new QTableWidgetItem{ ev.getLink().c_str() };
		link->setTextAlignment(Qt::AlignCenter);

		QPushButton* addToWishlist = new QPushButton{ "+" };
		addToWishlist->setStyleSheet("font-family: Verdana;font - size: 14px; font-weight: bold; color: #6780e4;");
		addWishlist.push_back(addToWishlist);

		QPushButton* openEvent = new QPushButton{ "Open" };
		openEvent->setStyleSheet("font-family: Verdana;font - size: 14px; font-weight: bold; color: #F78AFF;");
		openEvents.push_back(openEvent);

		table->setItem(rowNr, 0, t);
		table->setItem(rowNr, 1, description);
		table->setItem(rowNr, 2, date);
		table->setItem(rowNr, 3, time);
		table->setItem(rowNr, 4, participants);
		table->setCellWidget(rowNr, 5, openEvent);
		table->setCellWidget(rowNr, 6, addToWishlist);

		rowNr++;
	}
	table->resizeColumnsToContents();
	for (int i = 0; i < vec.size(); i++)
	{
		Event ev = vec[i];
		std::string command = "start " + ev.getLink();
		QObject::connect(openEvents[i], &QPushButton::clicked, this, [&, command]() {
			system(command.c_str());
			});
		QObject::connect(addWishlist[i], &QPushButton::clicked, this, [&, i]() {
			usr.addEventToWishlist(vec[i], i);
			});
	}
	QPushButton* exit = new QPushButton("Exit");
	exit->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	buttons->addWidget(exit);
	if (i!=0)
	{
		QPushButton* next = new QPushButton("Next");
		next->setStyleSheet("color: #FEDE8F; background-color: #856518;");
		buttons->addWidget(next);

		QObject::connect(next, &QPushButton::clicked, [&, i]() {
			user->hide();
			if (i != 12)
				seeEvents(i + 1);
			else
				seeEvents(1);
			});
	}
	QObject::connect(exit, &QPushButton::clicked, [&, i]() {
		user->hide();
		});

	mainLayout->addWidget(title);
	mainLayout->addWidget(table);
	mainLayout->addLayout(buttons);

	user->showMaximized();
	return user->exec();
}

int GUI::adminGUI() {

	QDialog* admin = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	admin->setLayout(mainLayout);

	QVBoxLayout* buttons = new  QVBoxLayout{};

	QLabel* title = new QLabel("Admin Menu");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QPushButton* addNewEvent = new QPushButton{};
	addNewEvent->setText("Add new event");
	addNewEvent->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	QObject::connect(addNewEvent, &QPushButton::clicked, this, &GUI::newEvent);

	QPushButton* seeAll = new QPushButton{};
	seeAll->setText("Show all events");
	seeAll->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	QObject::connect(seeAll, &QPushButton::clicked, this, &GUI::seeAllEvents);

	buttons->addWidget(addNewEvent);
	buttons->addWidget(seeAll);

	mainLayout->addWidget(title);
	mainLayout->addLayout(buttons);
	
	admin->setLayout(mainLayout);
	admin->baseSize();
	admin->show();
	return admin->exec();
}

int GUI::newEvent()
{
	QDialog* admin = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	admin->setLayout(mainLayout);
	
	QLabel* titleLabel = new QLabel("Add a new event");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QFormLayout* newEv = new QFormLayout();

	QLabel title("Title: ");
	QLabel description("Description: ");
	QLabel date ("Date: ");
	QLabel time ("Time: ");
	QLabel numberOfParticipants("Number of participants");
	QLabel link ("Link: ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	title.setBuddy(titleInput); 

	QLineEdit* descriptionInput = new QLineEdit();
	descriptionInput->setObjectName("description");
	description.setBuddy(descriptionInput);
	
	QDateTimeEdit* dateInput = new QDateTimeEdit(QDate(2024, 1,1), &date);
	dateInput->setObjectName("date");
	date.setBuddy(dateInput);

	QDateTimeEdit* timeInput = new QDateTimeEdit(QTime(0,0));
	timeInput->setObjectName("time");
	time.setBuddy(timeInput);

	QLineEdit* numberOfParticipantsInput = new QLineEdit();
	numberOfParticipantsInput->setObjectName("number od participants");
	numberOfParticipants.setBuddy(numberOfParticipantsInput);
	
	QLineEdit* linkInput = new QLineEdit();
	linkInput->setObjectName("link");
	link.setBuddy(linkInput);

	newEv->addRow(&title, titleInput);
	newEv->addRow(&description, descriptionInput);
	newEv->addRow(&date, dateInput);
	newEv->addRow(&time, timeInput);
	newEv->addRow(&numberOfParticipants, numberOfParticipantsInput);
	newEv->addRow(&link, linkInput);
	QPushButton addButton("Add");
	newEv->addRow(&addButton);

	QObject::connect(&addButton, &QPushButton::clicked, [&]() {
		try {
			QString TITLE = (*titleInput).text();
			QString DESCRIPTION = (*descriptionInput).text();

			dateInput->setDateRange(QDate(2020, 1, 1), QDate(2030, 1, 1));
			timeInput->setTimeRange(QTime(0, 0), QTime(23, 59));
			QDate DATE = dateInput->date();
			QTime TIME = timeInput->time();
			QString PARTICIPANTS = (*numberOfParticipantsInput).text();
			QString LINK = (*linkInput).text();
			adm.addEvent(TITLE.toStdString(), DESCRIPTION.toStdString(), LINK.toStdString(),TIME.hour(), TIME.minute(), DATE.day(),DATE.month(), DATE.year(), std::stoi(PARTICIPANTS.toStdString()));
		}
		catch (ValidationException& e)
		{
			ValidationExceptionInherited e1{ e.getMessage() };
		}
		admin->hide();
		});
	mainLayout->addLayout(newEv);
	
	admin->show();
	return admin->exec();
}

int GUI::updateEvent(int i)
{
	QDialog* admin = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	admin->setLayout(mainLayout);

	QLabel* titleLabel = new QLabel("New date for event");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QFormLayout* newEv = new QFormLayout();

	QLabel title("Title: ");
	QLabel description("Description: ");
	QLabel date("Date: ");
	QLabel time("Time: ");
	QLabel numberOfParticipants("Number of participants");
	QLabel link("Link: ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	title.setBuddy(titleInput);

	QLineEdit* descriptionInput = new QLineEdit();
	descriptionInput->setObjectName("description");
	description.setBuddy(descriptionInput);

	QDateTimeEdit* dateInput = new QDateTimeEdit(QDate(2024, 1, 1), &date);
	dateInput->setObjectName("date");
	date.setBuddy(dateInput);

	QDateTimeEdit* timeInput = new QDateTimeEdit(QTime(0, 0));
	timeInput->setObjectName("time");
	time.setBuddy(timeInput);

	QLineEdit* numberOfParticipantsInput = new QLineEdit();
	numberOfParticipantsInput->setObjectName("number od participants");
	numberOfParticipants.setBuddy(numberOfParticipantsInput);

	QLineEdit* linkInput = new QLineEdit();
	linkInput->setObjectName("link");
	link.setBuddy(linkInput);

	newEv->addRow(&title, titleInput);
	newEv->addRow(&description, descriptionInput);
	newEv->addRow(&date, dateInput);
	newEv->addRow(&time, timeInput);
	newEv->addRow(&numberOfParticipants, numberOfParticipantsInput);
	newEv->addRow(&link, linkInput);
	QPushButton* modifyButton = new QPushButton("Modify");
	newEv->addRow(modifyButton);
	QObject::connect(modifyButton, &QPushButton::clicked, [&]() {

		QString TITLE = (*titleInput).text();
		QString DESCRIPTION = (*descriptionInput).text();

		dateInput->setDateRange(QDate(2020, 1, 1), QDate(2030, 1, 1));
		timeInput->setTimeRange(QTime(0, 0), QTime(23, 59));

		QDate DATE = dateInput->date();
		QTime TIME = timeInput->time();
		QString PARTICIPANTS = (*numberOfParticipantsInput).text();
		QString LINK = (*linkInput).text();
		Event ev = adm.getRepository()[i];
		Event modified = Event(TITLE.toStdString(), DESCRIPTION.toStdString(), Date(DATE.day(), DATE.month(), DATE.year()), Time(TIME.hour(), TIME.minute()), std::stoi(PARTICIPANTS.toStdString()), LINK.toStdString());
		adm.updateEvent(ev.getTitle(), ev.getDate().getDay(), ev.getDate().getMonth(), ev.getDate().getYear(), modified.getTitle(),
			modified.getDescription(), modified.getLink(), modified.getTime().getHour(), modified.getTime().getMinute(), modified.getDate().getDay(),
			modified.getDate().getMonth(), modified.getDate().getYear(), modified.getNrOfParticipants());

		admin->hide();
		});

	mainLayout->addLayout(newEv);

	admin->show();
	
	return admin->exec();
}

int GUI::seeAllEvents()
{
	QDialog* admin = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	admin->setLayout(mainLayout);

	QLabel* title = new QLabel("Events");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QTableWidget* table = new QTableWidget();
	table->setRowCount(adm.getRepository().size());
	table->setColumnCount(8);
	table->setStyleSheet("background-color: #FEDE8F; color: #856518; font-size: 16px; font-weight: bold");

	QStringList header;
	header.append("Title");
	header.append("Description");
	header.append("Date");
	header.append("Time");
	header.append("Participants");
	header.append("Link");
	header.append("Remove");
	header.append("Modify");
	table->setHorizontalHeaderLabels(header);
	int rowNr = 0;
	std::vector<QPushButton*> removeButtons;
	std::vector<QPushButton*> editButtons;
	std::vector<QPushButton*> openEvents;
	
	std::vector<Event> events = adm.getRepository();
	for (auto ev : events)
	{
		QTableWidgetItem* t = new QTableWidgetItem{ ev.getTitle().c_str() };
		t->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* description = new QTableWidgetItem{ ev.getDescription().c_str() };
		description->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* date = new QTableWidgetItem{ ev.getDate().toString().c_str() };
		date->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* time = new QTableWidgetItem{ ev.getTime().toString().c_str() };
		time->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* participants = new QTableWidgetItem{ std::to_string(ev.getNrOfParticipants()).c_str() };
		participants->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* link = new QTableWidgetItem{ ev.getLink().c_str() };
		link->setTextAlignment(Qt::AlignCenter);

		QPushButton* removeButton = new QPushButton{ "X" };
		removeButton->setStyleSheet("font-family: Verdana; font-size: 16px; font-weight: bold; color: #f70808; ");
		removeButtons.push_back(removeButton);
		QPushButton* editButton = new QPushButton{ "Edit" };
		editButton->setStyleSheet("font-family: Verdana;font - size: 14px; font-weight: bold; color: #6780e4;");
		editButtons.push_back(editButton);
		
		QPushButton* openEvent = new QPushButton{ "Open" };
		openEvent->setStyleSheet("font-family: Verdana;font - size: 14px; font-weight: bold; color: #F78AFF;");
		openEvents.push_back(openEvent);

		table->setItem(rowNr, 0, t);
		table->setItem(rowNr, 1, description);
		table->setItem(rowNr, 2, date);
		table->setItem(rowNr, 3, time);
		table->setItem(rowNr, 4, participants);
		table->setCellWidget(rowNr, 5, openEvent);
		table->setCellWidget(rowNr, 6, removeButton);
		table->setCellWidget(rowNr, 7, editButton);

		rowNr++;
	}
	table->resizeColumnsToContents();
	for (int i= 0;i<events.size();i++)
	{
		Event ev = events[i];
		std::string command = "start " + ev.getLink();
		QObject::connect(openEvents[i], &QPushButton::clicked, this, [&, command]() {
			system(command.c_str());
			});
		QObject::connect(removeButtons[i], &QPushButton::clicked, this, [&, i]() {
			adm.removeEvent(events[i].getTitle(), events[i].getDate().getDay(), events[i].getDate().getMonth(), events[i].getDate().getYear());
			admin->hide();
			seeAllEvents();
			});
		QObject::connect(editButtons[i], &QPushButton::clicked, this, [&, i]() {
			updateEvent(i);
			admin->hide();
			seeAllEvents();
			});
	}
	mainLayout->addWidget(title);
	mainLayout->addWidget(table);

	admin->showMaximized();
	return admin->exec();
}

int GUI::userGUI() {

	usr.updateUserRepository();
	QDialog* user = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	user->setLayout(mainLayout);

	QVBoxLayout* buttons = new  QVBoxLayout{};

	QLabel* title = new QLabel("User Menu");
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("color: #856518; font-size: 20px; font-weight: bold; margin-bottom: 20px;");

	QPushButton* wishlist = new QPushButton{};
	wishlist->setText("See your events");
	wishlist->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	QObject::connect(wishlist, &QPushButton::clicked, this, &GUI::wishlist);

	QPushButton* seeEventsForMonth = new QPushButton{};
	seeEventsForMonth->setText("See events");
	seeEventsForMonth->setStyleSheet("color: #FEDE8F; background-color: #856518;");
	QObject::connect(seeEventsForMonth, &QPushButton::clicked, this, &GUI::seeEventsForMonthMenu);

	buttons->addWidget(wishlist);
	buttons->addWidget(seeEventsForMonth);

	mainLayout->addWidget(title);
	mainLayout->addLayout(buttons);

	user->setLayout(mainLayout);
	user->baseSize();
	user->show();
	return user->exec();
}

