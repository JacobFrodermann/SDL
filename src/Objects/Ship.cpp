#include "Ship.hpp"
#include <SDL3/SDL_rect.h>
#include "../Settings.hpp"
#include "Particle.hpp"
#include "Beam.hpp"
#include "SDL_pixels.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <spdlog/spdlog.h>


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
		srcRect = SDL_FRect{0,0,40,60};
		power = 3;
	}
	
	const SDL_FRect* Ship::getDstRect() {
		dstRect = SDL_FRect{static_cast<float>(X), static_cast<float>(Y) , static_cast<float>(W) ,static_cast<float>(H)};;
		return &dstRect;
	}
	
	const SDL_FRect* Ship::getSrcRect(int i) {
		if (Ship::player.dead) {
			srcRect.y = 4*60;
		} else {
			srcRect.y = 60 * i;
		}

		return &srcRect;
	}
	
	const SDL_FRect* Ship::getColRect() {
		colRect = SDL_FRect{
			static_cast<float>( X + 5  ),
		static_cast<float>( Y + 15 ),
		static_cast<float>( W - 5  ),
		static_cast<float>( H - 25 ),
	};
	return &colRect;
}

void Ship::shoot() {
	if (BeamCD < 0 && !dead) {
		Beam::shoot(X+20,Y+25,rotation, power); 
		BeamCD = BEAM_COOLDOWN;
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
	if (Ship::player.dead) return;

	VelY += i * cos(rotation);
	VelX += i * sin(rotation);

	spawnEngineParticle();
	spawnEngineParticle();
	spawnEngineParticle();
}

void Ship::spawnEngineParticle() {
	int colorChoice = Random::rand.nextUInt()%3;
	spdlog::info(colorChoice);
	SDL_Color partColor;
	switch (colorChoice) {
		case 0:
			partColor = {250, 70,70, 130};
			break;
		case 1:
			partColor = {250, 140, 50, 130};
			break;
		case 2:
			partColor = { 250, 207, 120, 130};
			break;
		default: 
			partColor = {0,0,0,0};
	}


	SDL_FPoint origin = {static_cast<float>(X+W/2), static_cast<float>(Y+H/2)};
	
	double rot = M_PI*1.45 - (rotation + Random::rand.nextFloat(.5)-.25);

	origin.x += cos(rot) * H/3;
	origin.y += sin(rot) * W/3;

	double PVelX = cos(rot) * -10;
	double PVelY = sin(rot) * -10;

	double speedFactor = .7 + Random::rand.nextFloat(.5) - .25;

	Particle::spawnParticle(origin.x, origin.y, -PVelX*speedFactor, -PVelY*speedFactor, 8, 5, partColor);

}

void Ship::rot(double i) {
	if (Ship::player.dead) return;
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