#include "Beam.hpp"
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
    for (Beam& b : Beam::beams) {
        b.X += b.VelX;
        b.Y += b.VelY;
        b.age++;
    }
}
void Beam::filter(){
    std::vector<Beam> temp = {};
    std::copy_if(beams.begin(),beams.end(),std::back_inserter(temp),[](Beam b){return b.age < 100;
    });
    beams = temp;
}