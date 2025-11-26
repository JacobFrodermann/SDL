#include "Ship.hpp"
#include "SDL_rect.h"
#include "../Settings.hpp"
#include "Beam.hpp"
#include <cmath>


namespace AsteroidShooter {

	
	Ship Ship::player = Ship();
	
	Ship::Ship() {
		X = 930;
		Y = 900;
		W = 60;
		H = 90;
		health = 3;
		BeamCD = 0;
		rotation = M_PI;
		srcRect = SDL_Rect{0,0,40,60};
		power = 3;
	}
	
	SDL_Rect* Ship::getDstRect() {
		dstRect = SDL_Rect{static_cast<int>(X), static_cast<int>(Y) , W ,H};;
		return &dstRect;
	}
	
	SDL_Rect* Ship::getSrcRect(int i) {
		srcRect.y = 60 * i;
		return &srcRect;
	}
	
	SDL_Rect Ship::getColRect() {
		return  SDL_Rect{
			static_cast<int>( X + 5  ),
		static_cast<int>( Y + 15 ),
		static_cast<int>( W - 5  ),
		static_cast<int>( H - 25 ),
	};
}

void Ship::shoot() {
	if (BeamCD < 0 && !dead) {
		Beam::shoot(X+20,Y+25,rotation, power); 
		BeamCD = BEAMCOOLDOWN;
	}
}

void Ship::tick() {
	X += VelX/1.5;
	Y += VelY/1.5;
	rotation += VelRot / 3;
	VelRot = VelRot / FRICTION_MOD;
	VelX = VelX / FRICTION_MOD;
	VelY = VelY / FRICTION_MOD;
	BeamCD --;
	invisFrames --;
}

void Ship::accel(double i) {
	VelY += i * cos(rotation);
	VelX += i * sin(rotation);
}

void Ship::rot(double i) {
	VelRot += i;
}

void Ship::damage(int i) {
	if (invisFrames < 0) { 
		health --;
		dead = health < 1; 
		invisFrames = 45;
	}
}
bool Ship::isInvis() {
	return invisFrames > 0;
}
void Ship::powerUp() {
	power ++;
}

int Ship::getHealth() {
	return this->health;
}
}