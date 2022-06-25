#include "User.h"

User::User(const std::string login, const std::string password, const std::string nickname)
	: login_(login), password_(password), nickname_(nickname) {}

const std::string& User::getLogin() const
{
	return login_;
}

const std::string& User::getPassword() const
{
	return password_;
}

void User::setPassword(const std::string& password)
{
	password_ = password;
}

const std::string& User::getNickname() const
{
	return nickname_;
}

void User::setNickname(const std::string& nickname)
{
	nickname_ = nickname;
}
