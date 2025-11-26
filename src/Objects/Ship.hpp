#pragma  once
#include <SDL3/SDL_rect.h>

namespace AsteroidShooter{

class Ship {
    private:
        SDL_FRect  srcRect, dstRect, colRect;
        int health, invisFrames;
    public:
        Ship();
        static Ship player;
        
        const SDL_FRect* getSrcRect(int), *getColRect(), *getDstRect();

        void shoot(), tick(), accel(double), rot(double), damage(int), powerUp();

        double VelX, VelY, VelRot,  X, Y, rotation;
        int BeamCD, W, H, power, getHealth();
        bool dead, isInvis();
};
}