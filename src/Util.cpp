#include <SDL.h>
#include <algorithm>
#include <vector>
#include "Util.hpp"

SDL_Rect util::rect(int x, int y, int w, int h) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;    
}
bool util::contains(SDL_Rect rect, SDL_Point point) {
    return rect.x <= point.x && rect.x+rect.w >= point.x && rect.y <= point.y && rect.y+rect.h >= point.y;
}

bool util::isPressed(std::vector<int> pressed, SDL_KeyCode key) {
	return std::find(pressed.begin(), pressed.end(), key) != pressed.end();
}
float util::random_float(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}
