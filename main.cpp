#include "OOP_A8.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
int main(int argc, char *argv[])
{
    {
		std::vector<Event> events, wishlist;
		Repository repo{ "events.txt", events };
		Repository wishlistRepo{ "wishlist.txt", wishlist };
		AdminService admin{ repo };
		UserService user{ repo, wishlistRepo };

		GUI gui(admin, user, argc, argv);
		gui.start();
    }
}
