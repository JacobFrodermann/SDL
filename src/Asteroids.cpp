#include "Asteroid.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include "SDL_rect.h"
#include "Ship.hpp"
#include "Util.hpp"
#include "Settings.hpp"

std::vector<Asteroid> Asteroid::asteroids = {};

Asteroid::Asteroid(int score) {
    w = 107;
    h = 112;
    radius = rand() % 30 + 35 + score / 5;
    health = round( (int)(radius / 50) + pow(radius,2) / 650); // f(x) = x/50 + x²/650
    rs = util::random_float(.1, 2);
    skin = std::rand() % 64;
    rot = util::random_float(5.5,7);
    X = rand()%960-80;
    Y = -120;
    if (rot < 6.25) X += 1100;
    VelX = sin(rot) * ASTEROIDSPEED;
    VelY = cos(rot) * ASTEROIDSPEED;
    spdlog::trace("Spawned Asteroid with Skin " + std::to_string(skin) + " Radius " + std::to_string(radius) + " Health " + std::to_string(health));
    Asteroid::asteroids.push_back(*this);
}

SDL_Rect Asteroid::getSrcRect() {
    SDL_Rect ret = SDL_Rect();
    ret.h = 112;
    ret.w = 107;
    ret.x = skin%8*102+20;
    ret.y = floor(skin/8)*102+30;
    return ret;
}
SDL_Rect Asteroid::getDstRect() {
    SDL_Rect ret = SDL_Rect();
    ret.h = 2.24 * radius;
    ret.w = 2.14 * radius;
    ret.x = X;
    ret.y = Y;
    return  ret;
}

void Asteroid::spawn(int score){
    if (rand() % ASTEROIDSPAWNRATE == 0) asteroids.push_back(Asteroid(score));
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
        if (a.health <= 0) {
            if (a.skin == 0 || a.skin == 8 || a.skin == 16) Ship::player.powerUp();
            return false;
        };
        return a.checkBounds();
    });
}  

bool Asteroid::intersects(SDL_Rect r) { // src: https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle
    bool hit = false;
    hit = hit || intersects(SDL_Point{r.x,r.y               });
    hit = hit || intersects(SDL_Point{r.x,r.y + r.h         });
    hit = hit || intersects(SDL_Point{r.x + r.w,r.y         });
    hit = hit || intersects(SDL_Point{r.x + r.w,r.y + r.h   });

    return hit;
}

bool Asteroid::intersects(SDL_Point p) {
    return util::inCircle(SDL_Point{
        static_cast<int>(X+w/2),
        static_cast<int>(Y+h/2)
    }, radius, p);
}

void Asteroid::damage() {
    health --;
    Asteroid::filter();
}

bool Asteroid::checkBounds() {
    return X < 2000 && X > -200 && Y < 1200 && Y > -200;
}