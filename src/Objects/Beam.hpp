#pragma once
#include <SDL3/SDL_rect.h>
#include <vector>


namespace AsteroidShooter {
    
    class Beam {
        private:
            void calcPoints();
            bool boundsCheck();
        public:
            Beam(float rot) : Beam(0,0, rot) {};
            Beam(float X, float Y, float rotation);
            float X,Y,VelX,VelY,rot; 
            int w, h;
            bool removeMe;
            static std::vector<Beam> beams;
            static void shoot(float X,float Y,float rotation, int power);
            SDL_FRect getDstRect();
            void tick();
            static void filter();
            SDL_FPoint head,tail;
    };
}