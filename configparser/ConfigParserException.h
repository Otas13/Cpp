#pragma once
#include <exception>

class ConfigParserException : public std::exception
{
public:
	ConfigParserException(char* m = "An exception occurred.") : msg(m) {}
	~ConfigParserException() throw() {}
	virtual const char* what() const throw() { return msg; }

private:
	char* msg;
};

