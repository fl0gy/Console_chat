#include "Chat.h"
using namespace std;

int main()
{
	Chat chat;
    chat.start();

	while (chat.chatIsWork())
	{
		chat.showLoginMenu();
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	return 0;
}