#include "Asteroid.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "SDL_rect.h"
#include "Util.hpp"
#include "Settings.hpp"

std::vector<Asteroid> Asteroid::asteroids = {};

Asteroid::Asteroid() {
    w = 107;
    h = 112;
    radius = 50;
    health = ASTEROIDHEALTH;
    rs = util::random_float(.1, 2);
    skin = std::rand() % 64;
    rot = util::random_float(5.5,7);
    X = rand()%960-80;
    Y = -120;
    if (rot < 6.25) X += 1100;
    VelX = sin(rot) * ASTEROIDSPEED;
    VelY = cos(rot) * ASTEROIDSPEED;
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
    ret.h = 112;
    ret.w = 107;
    ret.x = X;
    ret.y = Y;
    return  ret;
}

void Asteroid::spawn(){
    if (rand() % ASTEROIDSPAWNRATE == 0) asteroids.push_back(Asteroid());
}
void Asteroid::tick() {
    X += VelX;
    Y += VelY;
    rot += rs;
}
void Asteroid::filter() {
    std::vector<Asteroid> temp = {};
    std::copy_if(asteroids.begin(), asteroids.end(), std::back_inserter(temp),[](Asteroid a) -> bool{
        if (a.health <= 0) {
            return false;
        };
        return a.X < 2000 && a.X > -200 && a.Y < 1200 && a.Y > -200;
    });
    asteroids = temp;
}  

bool Asteroid::intersects(SDL_Point p) { // src: https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle
    return util::inCircle(SDL_Point{
        static_cast<int>(X+w/2),
        static_cast<int>(Y+h/2)
    }, radius, p); 
}

void Asteroid::damage() {
    health --;
    Asteroid::filter();
}