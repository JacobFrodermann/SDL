#include <SDL3/SDL.h>
#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <vector>
#include "Util.hpp"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

namespace AsteroidShooter {

SDL_Rect Util::rect(int x, int y, int w, int h) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;    
}
bool Util::contains(SDL_FRect rect, SDL_FPoint point) {
    return rect.x <= point.x && rect.x+rect.w >= point.x && rect.y <= point.y && rect.y+rect.h >= point.y;
}

bool Util::isPressed(std::vector<int> pressed, SDL_Keycode key) {
    return std::find(pressed.begin(), pressed.end(), key) != pressed.end();
}

bool Util::isPressed(std::vector<int> pressed, std::initializer_list<SDL_Keycode> key) {
    for (SDL_Keycode k : key) {
        if (std::find(pressed.begin(), pressed.end(), k) != pressed.end()) return true;
    }
    return false;
}

float Util::random_float(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

SDL_Texture* Util::loadTexuture(std::string name, SDL_Renderer *renderer) {
    SDL_Surface *surf = IMG_Load(name.c_str());
    if (!surf) {
        spdlog::error(SDL_GetError());
        spdlog::error("failed to load texture " + name);
        exit(1);
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    return tex;
}
bool Util::inCircle(SDL_FPoint center, int radius, SDL_FPoint p) {
    int dx = std::abs(center.x - p.x);
    if (dx > radius) return false;
    int dy = std::abs(center.y - p.y);
    if (dy > radius) return false;
    if (dx+dy <= radius) return true;
    return (dx*dx + dy*dy <= radius*radius);
}
}