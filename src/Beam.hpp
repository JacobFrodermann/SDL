#pragma once
#include "SDL_rect.h"
#include <vector>

class Beam {
    public:
        Beam(float X, float Y, float rotation);
        float X,Y,VelX,VelY,rot; 
        int w, h;
        static std::vector<Beam> beams;
        static void shoot(float X,float Y,float rotation);
        SDL_Rect getDstRect();
        void tick();
        static void filter();
        SDL_Point* points;
};