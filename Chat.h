#pragma once
#include "Message.h"
#include <memory>
#include <exception>
#include <vector>

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override;
};

struct UserNicknameExp : public std::exception
{
	const char* what() const noexcept override;
};

class Chat
{
	bool chatIsWork_ = false;
	std::vector<User> users_;
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_ = nullptr;
    void signIn();
	void signUp();
	void showChat() const;
	void addMessage();
	void showUsers() const;
	std::vector<User> getAllUsers();
	std::vector<Message> getAllMessages();
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByNickname(const std::string& nickname) const;
public:
	void start();
	bool chatIsWork() const;
	std::shared_ptr<User> getCurrentUser() const;
	void showLoginMenu();
	void showUserMenu();
};

