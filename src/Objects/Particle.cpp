#include "Particle.hpp"
#include "SDL_rect.h"
#include <cmath>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <vector>

namespace AsteroidShooter {
    

    std::vector<Particle> Particle::particles = {};
    Random Particle::random = Random();

    SDL_Rect Particle::getRect() {
        return SDL_Rect{x, y, size, size};
    }

    void Particle::spawnParticle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color c) {
            Particle::particles.push_back({x, y, xV, yV, liveTime, size, c});
    }
    
    void Particle::explosion(int x, int y, double xV, double yV, int power, SDL_Color c) {
        for (int i = 0; i < static_cast<int>(sqrt(power)); i ++) {
            double Xoffset = rand() % power / 5.0 - power / 10.0;
            double Yoffset = rand() % power / 5.0 - power / 10.0;
            double sizeOffset = 1 + (random.nextFloat(.5) - .25);

            Particle::particles.push_back({
                x, 
                y, 
                xV + Xoffset, 
                yV + Yoffset, 
                power*3, 
                static_cast<int>(power*sizeOffset), 
                c
            });
        }
    }

    Particle::Particle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color c) {
        this->x = x;
        this->y = y;
        this->xV = xV;
        this->yV = yV;
        this->liveTime = liveTime;
        this->size = size;
        this->color = c;
    }

    void Particle::tick() {
        std::vector<Particle> filtered = {};
        for (Particle& p : Particle::particles) {
            if (p.liveTime < 0) continue;

            p.x += p.xV;
            p.y += p.yV;

            p.liveTime --;

            filtered.push_back(p);
        }

        Particle::particles = filtered;
    }    

    SDL_Color Particle::getDrawColor() {
        SDL_Color col = color;
        col.r += rand() % variation.r - variation.r/2;
        col.g += rand() % variation.g - variation.g/2;        
        col.b += rand() % variation.b - variation.b/2;
        col.a += rand() % variation.a - variation.a/2;
        return col;
    }
}