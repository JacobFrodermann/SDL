#include "Asteroid.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include "Ship.hpp"
#include "Particle.hpp"
#include "../Utils/Util.hpp"
#include "../Settings.hpp"

namespace AsteroidShooter {

    
    std::vector<Asteroid> Asteroid::asteroids = {};
    
    Asteroid::Asteroid(int score) {
        w = 107;
        h = 112;
        radius = Random::rand.nextUInt() % 30 + 35 + score / 5;
        health = 2;//round( (int)(radius / 50) + pow(radius,2) / 650); // f(x) = x/50 + x²/650
        rs = Util::random_float(.1, 2);

        skin = Random::rand.nextUInt() % 64;
        rot = Util::random_float(5.5,7);
        X = rand()%960-80;
        Y = -120;
        if (rot < 6.25) X += 1100;
        VelX = sin(rot) * ASTEROID_SPEED;
        VelY = cos(rot) * ASTEROID_SPEED;
        spdlog::trace("Spawned Asteroid with Skin " + std::to_string(skin) + " Radius " + std::to_string(radius) + " Health " + std::to_string(health));
        Asteroid::asteroids.push_back(*this);
}

const SDL_FRect Asteroid::getSrcRect() {
    return SDL_FRect{
        .x = static_cast<float>(skin%8*102+20),
        .y = static_cast<float>(floor(skin/8)*102+30),
        .w = 107,
    .h = 112,
    };
}
const SDL_FRect Asteroid::getDstRect() {
    return SDL_FRect{
        .x = X,
        .y = Y,
        .w = static_cast<float>(2.14 * radius),
        .h = static_cast<float>(2.24 * radius),
    };
}

void Asteroid::spawn(int score){
    if (rand() % ASTEROID_SPAWNRATE == 0) asteroids.push_back(Asteroid(score));
}
void Asteroid::tick() {
    for (Asteroid &a : asteroids) {
        a.X += a.VelX;
        a.Y += a.VelY;
        a.rot += a.rs;
    }
}
void Asteroid::filter() {
    std::vector<Asteroid> temp = {};
    std::copy_if(asteroids.begin(), asteroids.end(), std::back_inserter(temp),[](Asteroid a) -> bool{
        if (a.health <= 0 || a.removeMe) {
            if (a.skin == 0 || a.skin == 8 || a.skin == 16) Ship::player.powerUp();
            
            Particle::explosion(a.X + a.w/2, a.Y + a.h /2, a.VelX, a.VelY, 10, SDL_Color{72,72,72, 50});
            return false;
        };
        return a.checkBounds();
    });

    Asteroid::asteroids = temp;
}  

bool Asteroid::intersects(const SDL_FRect* r) { // src: https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle
    bool hit = false;
    hit = hit || intersects(SDL_FPoint{r->x,r->y               });
    hit = hit || intersects(SDL_FPoint{r->x,r->y + r->h        });
    hit = hit || intersects(SDL_FPoint{r->x + r->w,r->y        });
    hit = hit || intersects(SDL_FPoint{r->x + r->w,r->y + r->h });

    if (hit) {
        spdlog::info("hit at {} {}", r->x, r->y);
    }
    
    return hit;
}

bool Asteroid::intersects(SDL_FPoint p) {
    SDL_FPoint center = {
        +w/2,
        Y+h/2
    };
    

    bool temp = Util::inCircle(center, radius, p);
    
    if (temp) {
        spdlog::info("hit at {} {}", p.x, p.y);
    }

    return temp;
}

void Asteroid::damage() {
    health --;

    if (health == 0) removeMe = true;
    //spdlog::info(health);
}

bool Asteroid::checkBounds() {
    return X < 2000 && X > -200 && Y < 1200 && Y > -200;
}

}