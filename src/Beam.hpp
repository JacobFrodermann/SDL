#pragma once
#include "SDL_rect.h"
#include <vector>

class Beam {
    public:
        float X,Y,VelX,VelY,rot;
        int age;
        static std::vector<Beam> beams;
        static void shoot(float X,float Y,float rotation);
        SDL_Rect getDstRect();
        void tick();
        static void filter();
};