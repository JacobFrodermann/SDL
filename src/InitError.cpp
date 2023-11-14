#include "InitError.h" 
#include <SDL.h>

InitError::InitError() :
	exception(),
	msg(SDL_GetError()) {
}

InitError::InitError(const std::string& m) :
	exception(),
	msg(m) {}

InitError::~InitError() throw() {}

const char* InitError::what() const throw() {
	return msg.c_str();
}