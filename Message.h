#pragma once
#include <string>
#include "User.h"

// "using namespace std" - Not used for better understanding of the code

class Message
{
	const std::string from_;
	const std::string to_;
	const std::string text_;
public:
	Message(const std::string& from, const std::string& to, const std::string& text);
	const std::string &getFrom() const;
	const std::string &getTo() const;
	const std::string &getText() const;
};

