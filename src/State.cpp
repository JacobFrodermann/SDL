#include "State.hpp"
#include <iostream>

int State::draw(SDL_Renderer * renderer) {std::cout<<"this should not be called (State::draw)";return 0;};
int State::init(SDL_Renderer * renderer) {std::cout<<"this should not be called (State::init)";return 0;};
State::~State() {};