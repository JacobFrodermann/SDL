#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>
#include <initializer_list>
#include <vector>
#include <SDL_image.h>
#include <string>

class util {
    public:
    static SDL_Rect rect(int x, int y, int w, int h);
    static bool contains(SDL_Rect rect, SDL_Point point);
    static bool isPressed(std::vector<int> pressed, SDL_KeyCode key);
    static bool isPressed(std::vector<int> pressed, std::initializer_list<SDL_KeyCode> key);
    static float random_float(float min, float max);
    static SDL_Texture* loadTexuture(std::string name, SDL_Renderer* renderer);
    static bool inCircle(SDL_Point center, int radius, SDL_Point p);
};