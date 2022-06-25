#pragma once
#include <string>

class User
{
	const std::string login_;
	std::string password_;
	std::string nickname_;
public:
	User(const std::string login, const std::string password, const std::string nickname);
	const std::string& getLogin() const;
	const std::string& getPassword() const;
	void setPassword(const std::string& password);
	const std::string& getNickname() const;
	void setNickname(const std::string& nickname);
};

