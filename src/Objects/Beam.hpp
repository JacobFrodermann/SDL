#pragma once
#include "SDL_rect.h"
#include <vector>

class Beam {
    private:
    public:
        Beam(float rot) : Beam(0,0, rot) {};
        Beam(float X, float Y, float rotation);
        float X,Y,VelX,VelY,rot; 
        int w, h;
        bool removeMe;
        static std::vector<Beam> beams;
        static void shoot(float X,float Y,float rotation, int power);
        SDL_Rect getDstRect();
        void tick();
        static void filter();
        SDL_Point* points;
};