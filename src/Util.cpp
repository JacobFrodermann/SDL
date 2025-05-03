#include <SDL.h>
#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <vector>
#include "Util.hpp"
#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"

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

bool util::isPressed(std::vector<int> pressed, std::initializer_list<SDL_KeyCode> key) {
    for (SDL_KeyCode k : key) {
        if (std::find(pressed.begin(), pressed.end(), k) != pressed.end()) return true;
    }
    return false;
}

float util::random_float(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}

SDL_Texture* util::loadTexuture(std::string name, SDL_Renderer *renderer) {
    SDL_Surface *temp = IMG_Load(name.c_str());
    if (temp == NULL) {
        spdlog::error(SDL_GetError());
        spdlog::error("failed to load texture " + name);
        exit(1);
    }
    return SDL_CreateTextureFromSurface(renderer, temp);
}
bool util::inCircle(SDL_Point center, int radius ,SDL_Point p ) {
  int dx = std::abs(center.x - p.x);
  if (dx > radius) return false;
  int dy = std::abs(center.y - p.y);
  if (dy > radius) return false;
  if (dx+dy <= radius) return true;
  return (dx*dx + dy*dy <= radius*radius);
}