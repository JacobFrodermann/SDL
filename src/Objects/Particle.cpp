#include "Particle.hpp"
#include <SDL3/SDL_rect.h>
#include <cmath>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>

namespace AsteroidShooter {
    

    std::vector<Particle> Particle::particles = {};

    SDL_FRect Particle::getRect() {
        return SDL_FRect{
            static_cast<float>(x), 
            static_cast<float>(y), 
            static_cast<float>(size), 
            static_cast<float>(size)
        };
    }

    void Particle::spawnParticle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color color) {
        spawnParticle(x, y , xV, yV, liveTime, size, color, {10,10,10});
    }
    
    void Particle::spawnParticle(int x, int y, double xV, double yV, int liveTime, int size, SDL_Color color, SDL_Color var) {
        Particle::particles.push_back({x, y, xV, yV, liveTime, size, color});
    }
    
    void Particle::explosion(int x, int y, double xV, double yV, int power, SDL_Color c) {
        for (int i = 0; i < static_cast<int>(sqrt(power)); i ++) {
            double Xoffset = rand() % power / 5.0 - power / 10.0;
            double Yoffset = rand() % power / 5.0 - power / 10.0;
            double sizeOffset = 1 + (Random::rand.nextFloat(.5) - .25);

            Particle::particles.push_back({
                x, 
                y, 
                xV + Xoffset, 
                yV + Yoffset, 
                power*3, 
                static_cast<int>((power/2)*sizeOffset), 
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
        this->initialLiveTime = liveTime;
        if (initialLiveTime == 0) initialLiveTime = 1;

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
        col.r = std::clamp(col.r + vary(variation.r), 0 ,255);
        col.g = std::clamp(col.g + vary(variation.g), 0, 255);        
        col.b = std::clamp(col.b + vary(variation.b), 0, 255);
        col.a = std::clamp(col.a + vary(variation.a) - fade(), 0, 255);
        
        return col;
    }

    int Particle::vary(int i) {
        return  Random::rand.nextInt() % i - i/2;
    }

    int Particle::fade() {
        return color.a * (1.0 - static_cast<float>(liveTime) / initialLiveTime);
    }
}