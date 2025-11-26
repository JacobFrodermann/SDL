#include "Beam.hpp"
#include <SDL3/SDL_rect.h>
#include "../Settings.hpp"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <spdlog/spdlog.h>
#include <vector>

namespace AsteroidShooter {
    
    
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
        this->VelX=BEAM_SPEED * sin(rotation);
        this->VelY=BEAM_SPEED * cos(rotation);
        this->rot = rotation;
        this->w = 25;
        this->h = 50;
        this->removeMe = false;
        
        calcPoints();
    }
    
    void Beam::shoot(float X, float Y, float rotation, int power){
        spdlog::info("Spawned beam at {} {}", X, Y);
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
    
    calcPoints();
}

SDL_FRect Beam::getDstRect() {
    return SDL_FRect{
    .x = X,
    .y = Y,
    .w = static_cast<float>(w),
    .h = static_cast<float>(h),
    };
}

void Beam::filter(){
    std::vector<Beam> temp = {};
    std::copy_if(beams.begin(),beams.end(),std::back_inserter(temp),[](Beam b){
        return b.X < 2000 && b.X > -200 && b.Y < 1200 && b.Y > -200 && !b.removeMe;
    });
    beams = temp;
}

void Beam::calcPoints() {
    head = {
        .x = static_cast<float>((X + w / 2.0) - (sin(rot) * 20)),
        .y = static_cast<float>((Y + h / 2.0) - (cos(rot) * 20))
    };
    tail = {
        .x = static_cast<float>((X + w / 2.0) + (sin(rot) * 20)),
        .y = static_cast<float>((Y + h / 2.0) + (cos(rot) * 20))
    };
}

}