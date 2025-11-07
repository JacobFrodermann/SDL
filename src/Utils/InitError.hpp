#pragma once
#include <string>
#include <exception>

class InitError : public std::exception {
	std::string msg;
public:
	InitError();
	InitError(const std::string&);
	virtual ~InitError() throw();
	virtual const char* what() const throw();
};