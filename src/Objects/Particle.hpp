#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <vector>
#include "../Utils/Random.hpp"

namespace AsteroidShooter {
    class Particle{
        public:
            Particle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color c);
            int x,y, size;
            
            SDL_Color getDrawColor();
            static std::vector<Particle> particles;
            
            static void spawnParticle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color c);
            static void spawnParticle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color c, SDL_Color v);
            
            static void explosion(int x, int y, double xV, double yV, int stength, SDL_Color c);
            SDL_FRect getRect();
            
            static void tick();
        private:
            SDL_Color color, variation = {10, 10 ,10 ,10};
            double xV, yV;
            int liveTime;
    };
}