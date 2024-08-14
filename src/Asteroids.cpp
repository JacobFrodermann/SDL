#include "Asteroid.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "SDL_rect.h"
#include "Util.hpp"
#include "Settings.hpp"

std::vector<Asteroid> Asteroid::asteroids = {}; //initalize the Vector

Asteroid::Asteroid() {
    w = 107;
    h = 112;
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

/*
for (int i=0; i<astAtlas.length; i++) {
			for (int j = 0; j<astAtlas[i].length; j++) {
				astAtlas[i][j] = atlas.getSubimage(i*102+20, j*102+30, 107, 112);
			} 
		}*/