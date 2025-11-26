#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>
#include <initializer_list>
#include <vector>
#include <SDL3/SDL_surface.h>
#include <string>

namespace AsteroidShooter {

    class Util {
        public:
        static SDL_Rect rect(int x, int y, int w, int h);
        static bool contains(SDL_FRect rect, SDL_FPoint point);
        static bool isPressed(std::vector<int> pressed, SDL_Keycode key);
        static bool isPressed(std::vector<int> pressed, std::initializer_list<SDL_Keycode> key);
        static float random_float(float min, float max);
        static SDL_Texture* loadTexuture(std::string name, SDL_Renderer* renderer);
        static bool inCircle(SDL_FPoint center, int radius, SDL_FPoint p);
    };
}