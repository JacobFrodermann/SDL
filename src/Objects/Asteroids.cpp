#include "Asteroid.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
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
    asteroids.erase(
        std::remove_if(asteroids.begin(), asteroids.end(),
        [](Asteroid& a) -> bool {
        return a.removeMe || a.checkBounds() || a.health <= 0;
        }
    ), asteroids.end());
}  

bool Asteroid::intersects(const SDL_FRect* r) {
    return     intersects(SDL_FPoint{r->x,r->y               })
            || intersects(SDL_FPoint{r->x,r->y + r->h        })
            || intersects(SDL_FPoint{r->x + r->w,r->y        })
            || intersects(SDL_FPoint{r->x + r->w,r->y + r->h });
}

bool Asteroid::intersects(SDL_FPoint p) {
    return Util::inCircle({X+w/2, Y+h/2}, radius, p);
}

void Asteroid::damage() {
    health --;

    if (health == 0) removeMe = true;
            
    if (skin == 0 || skin == 8 || skin == 16) Ship::player.powerUp();
            
    Particle::explosion(X + w/2, Y + h /2, VelX, VelY, 10, SDL_Color{72,72,72, 120});
}

bool Asteroid::checkBounds() {
    return X > 2000 || X < -200 || Y > 1200 || Y < -200;
}

}