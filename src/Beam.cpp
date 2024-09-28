#include "Beam.hpp"
#include "SDL_rect.h"
#include "Settings.hpp"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include <iostream>

std::vector<Beam> Beam::beams = {};

void Beam::shoot(float X, float Y, float rotation){
    Beam* temp = new Beam();
    temp->X = X;
    temp->Y=Y;
    temp->VelX=BEAMSPEED * sin(rotation);
    temp->VelY=BEAMSPEED * cos(rotation);
    temp->rot = rotation;
    temp->age = 0;
    Beam::beams.push_back(*temp);
}
void Beam::tick() {
    X += VelX;
    Y += VelY;
    age++;
}
SDL_Rect Beam::getDstRect() {
    SDL_Rect ret = SDL_Rect();
    ret.x = X;
    ret.y = Y;
    ret.w = 25;
    ret.h = 50;
    return ret;
}
void Beam::filter(){
    std::vector<Beam> temp = {};
    std::copy_if(beams.begin(),beams.end(),std::back_inserter(temp),[](Beam b){return b.age < 100;
    });
    beams = temp;
}

SDL_Point* Beam::getPoints() {
    SDL_Point ret[] = {{
        .x = static_cast<int>(X - sin(rot) * 12.5),
        .y = static_cast<int>(Y - cos(rot) * 25)
    },{
        .x = static_cast<int>(X + sin(rot) * 12.5),
        .y = static_cast<int>(Y + cos(rot) *25)
    }};
    return ret;
}
