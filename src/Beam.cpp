#include "Beam.hpp"
#include "SDL_rect.h"
#include "Settings.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

std::vector<Beam> Beam::beams = {};
Beam templates[15]=  {  Beam(0), 
                        Beam(0), Beam(0),
                        Beam(.1), Beam(0), Beam(-.1),
                        Beam(.2), Beam(.1), Beam(-.1), Beam(-.2),
                        Beam(.2), Beam(.1), Beam(0), Beam(.1), Beam(.2)
                    };
    

Beam::Beam(float X, float Y, float rotation) {
    this->X = X;
    this->Y=Y;
    this->VelX=BEAMSPEED * sin(rotation);
    this->VelY=BEAMSPEED * cos(rotation);
    this->rot = rotation;
    this->points = (SDL_Point*) malloc(sizeof(SDL_Point)*2);
    this->w = 25;
    this->h = 50;
    this->removeMe = false;
}

void Beam::shoot(float X, float Y, float rotation, int power){
    if (power > 5) power = 5;
    int offset = 0;
    for (int i = 0; i<power;i++) {
        offset += i;
    }
    for (int i = offset; i < offset + power; i++) {
        Beam::beams.push_back(*new Beam(X, Y, templates[i].rot + rotation));
    }
}
void Beam::tick() {
    X += VelX;
    Y += VelY;
    
    points[0] = {
        .x = static_cast<int>((X + w / 2) - (sin(rot) * 20)),
        .y = static_cast<int>((Y + h / 2) - (cos(rot) * 20))
    };
    points[1] = {
        .x = static_cast<int>((X + w / 2) + (sin(rot) * 20)),
        .y = static_cast<int>((Y + h / 2) + (cos(rot) * 20))
    };
}
SDL_Rect Beam::getDstRect() {
    SDL_Rect ret = SDL_Rect();
    ret.x = X;
    ret.y = Y;
    ret.w = w;
    ret.h = h;
    return ret;
}
void Beam::filter(){
    std::vector<Beam> temp = {};
    std::copy_if(beams.begin(),beams.end(),std::back_inserter(temp),[](Beam b){
        return b.X < 2000 && b.X > -200 && b.Y < 1200 && b.Y > -200 && !b.removeMe;
    });
    beams = temp;
}

