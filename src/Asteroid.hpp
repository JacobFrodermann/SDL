#pragma once
#include "SDL_rect.h"
#include <vector>
class Asteroid {
    public:
        Asteroid();
        SDL_Rect getSrcRect();
        SDL_Rect getDstRect();
        void tick();
        float X,Y,VelX,VelY,rot,h,w,rs;
        static std::vector<Asteroid> asteroids;
        static void spawn();
    private:
        int skin;
};