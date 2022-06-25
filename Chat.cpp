#include <iostream>
#include "Chat.h"

void Chat::start() // Function to start a chat
{
	chatIsWork_ = true;
}

void Chat::signIn() // Authorization for an existing user
{
	std::string login, password;
	char command;

	do
	{
		std::cout << "Login: ";
		std::cin >> login;
		std::cout << "Password: ";
		std::cin >> password;
		std::cout << std::endl;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getPassword()))  // If a non-existent login or an incorrect password is entered, you can exit to the main menu or try to log in again
		{
			currentUser_ = nullptr;
			std::cout << "**Login failed!**" << std::endl;
			std::cout << "**This user was not found**" << std::endl;
			std::cout << "**Enter (1) to exit or (2) to repeat**" << std::endl;
			std::cout << std::endl;
			std::cin >> command;
			if (command == '1')
			{
				break;
			}
		}
	} while (!currentUser_);
}

void Chat::signUp() // User registration
{
	std::string login, password, nickname;

	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	std::cout << std::endl;

	if (getUserByLogin(login) || login == "all") // If the login is busy, a corresponding message is displayed
	{
		throw UserLoginExp();
	}
	if (getUserByNickname(nickname) || nickname == "all") // If the nickname is busy, a corresponding message is displayed
	{
		throw UserNicknameExp();
	}
	User user = User(login, password, nickname);
	users_.push_back(user);
	currentUser_= std::make_shared<User> (user);
}

void Chat::showChat() const  // Chat display (all messages)
{
	std::string from;
	std::string to;
	std::cout << "~~~CHAT~~~" << std::endl;
	std::cout << std::endl;

	for (auto& allmess : messages_)
	{
		if (currentUser_->getLogin() == allmess.getFrom() || currentUser_->getLogin() == allmess.getTo() || allmess.getTo() == "all")
		{
			from = (currentUser_->getLogin() == allmess.getFrom()) ? "me" : getUserByLogin(allmess.getFrom())->getNickname();
			if (allmess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser_->getLogin() == allmess.getTo()) ? "me" : getUserByLogin(allmess.getFrom())->getNickname();
			}
			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: " << allmess.getText() << std::endl;
			std::cout << std::endl;
		}
	}
	std::cout << "~~~~~~~~~" << std::endl;
}

void Chat::addMessage() // Add a message to the chat for everyone or for a specific user
{
	std::string to, text;
	std::cout << "To (enter a nickname or write to everyone(all)): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserByNickname(to)))
	{
		std::cout << "  Error sending message, user with this nickname was not found!  " << to << std::endl;
		return;
	}
	if (to == "all")
	{
		messages_.push_back(Message(currentUser_->getLogin(), "all", text));
	}
	else
	{
		messages_.push_back(Message(currentUser_->getLogin(), getUserByNickname(to)->getLogin(), text));
	}
}

void Chat::showUsers() const // Show existing users
{
	std::cout << "A list of User:" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getNickname();
		if (currentUser_->getLogin() == user.getLogin())
		{
			std::cout << "(me)";
		}
		std::cout << std::endl;
	}
	std::cout << "~~~~~~~~~~~~~~~" << std::endl;
}

std::vector<User> Chat::getAllUsers()
{
	return users_;
}

std::vector<Message> Chat::getAllMessages()
{
	return messages_;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto &user : users_)
	{
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByNickname(const std::string& nickname) const
{
	for (auto &user : users_)
	{
		if (nickname == user.getNickname())
			return std::make_shared<User>(user);
	};
	return nullptr;
}

bool Chat::chatIsWork() const
{
	return chatIsWork_;
}

std::shared_ptr<User> Chat::getCurrentUser() const
{
	return currentUser_;
}

void Chat::showLoginMenu() // Show Login Menu
{
	currentUser_ = nullptr;
	char command;
	std::cout << "**Hello! You have entered the console chat! Select an operation to continue.**" << std::endl;
	
	do
	{
		std::cout << ">>> 1 - Sign In | 2 - Sign Up | 3 - Exit <<<" << std::endl;
		std::cout << ">>> ";
		std::cin >> command;
		switch (command)
		{
		case '1':
			signIn();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '3':
			chatIsWork_ = false;
			break;
		default:
			std::cout << ">>> Wrong choice! <<<" << std::endl;
			std::cout << ">>> Enter 1 or 2 <<<" << std::endl;
			break;
		}
	} while (!currentUser_ && chatIsWork_);
}

void Chat::showUserMenu() // Show User Menu
{
	char command;
	std::cout << "You have entered the user menu! Select a section to continue, " << currentUser_->getNickname() << std::endl;

	while (currentUser_)
	{
		std::cout << ">>> 1 - Show all users | 2 - Show all messages (show chat) | 3 - Add message to chat | 4 - Sign Out <<<" << std::endl;
		std::cout << ">>> ";
		std::cin >> command;
		switch (command)
		{
		case '1':
			showUsers();
			break;
		case '2':
			showChat();
			break;
		case '3':
			addMessage();
			break;
		case '4':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "Wrong choice!" << std::endl;
			break;
		}
	}
}

const char* UserLoginExp::what() const noexcept // The function displays a warning that the login is already in use.
{
	return "User login is busy";
}

const char* UserNicknameExp::what() const noexcept // The function displays a warning that the nickname is already in use.
{
	return "User nickname is busy";
}
