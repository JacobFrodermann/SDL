#pragma  once
#include "SDL_rect.h"

namespace AsteroidShooter{

class Ship {
    private:
        SDL_Rect  srcRect, dstRect;
        int health, invisFrames;
    public:
        Ship();
        static Ship player;
        SDL_Rect* getDstRect();
        SDL_Rect* getSrcRect(int);
        SDL_Rect getColRect();
        void shoot(), tick(), accel(double), rot(double), damage(int), powerUp();
        double VelX, VelY, VelRot,  X, Y, rotation;
        int BeamCD, W, H, power, getHealth();
        bool dead, isInvis();
};
}