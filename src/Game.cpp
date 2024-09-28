#include "Game.hpp"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>
#include <vector>
#include "Settings.hpp"
#include "Util.hpp"
#include "Beam.hpp"
#include "Asteroid.hpp"

int Game::init(SDL_Renderer * renderer) {
	this->BgTexture = util::loadTexuture("assets/GameBG.png", renderer);
	this->ShipsTexture = util::loadTexuture("assets/Ships.png", renderer);
	this->BeamTexture = util::loadTexuture("assets/beam.png",renderer);
	this->AsteroidsTexture = util::loadTexuture("assets/asteriodAtlas.png", renderer);


	this->BgRect = {690,0,540,2160};

	BackgroundOffset = 0;
	VelX = 0;
	VelY = 0;
	ShipRect = {920,900,60,90};
	X = ShipRect.x;
	Y = ShipRect.y;
	animationState = 0;
	dead = false;
	ShipSrcRect = {0,0,40,60};
	pressed = {};
	rotation = M_PI;
	BeamCD=0;
	return 0;
}

int Game::draw(SDL_Renderer * render) {
	this->renderer = render;
	tick ++;
	tick %= 20;
	int ret = 0;
	SDL_Event e;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT) {
			ret = SDL_QUIT;
		} else if (e.type == SDL_KEYDOWN) {
			pressed.push_back(e.key.keysym.sym);
		} else if (e.type == SDL_KEYUP) {
			pressed.erase(std::remove(pressed.begin(), pressed.end(), e.key.keysym.sym), pressed.end());
		}
	}

	handleKeyPresses();
	
	BeamCD--;
	X += VelX/1.5;
	Y += VelY/1.5;
	VelX = VelX / FRICTION_MOD;
	VelY = VelY / FRICTION_MOD;


	ShipRect.x = X;
	ShipRect.y = Y;
	
	BackgroundOffset -= .1f;
	animationState += .05f;
	if ((int) animationState == 4) animationState = 0; //reset animation before 5

	ShipSrcRect.y = (int) animationState * 60; //move Rect to fitting image
	ShipSrcRect.y = (int) animationState * 60; //move Rect to fitting image

	if (tick == 1) {
		Beam::filter();
		Asteroid::filter();
	}


	Asteroid::spawn();
	
	renderAsteroids();

	renderBeams();

	doCollisions();

	SDL_RenderCopyEx(renderer, ShipsTexture, &ShipSrcRect, &ShipRect,(rotation-M_PI)*-180/M_PI,NULL,SDL_FLIP_NONE);

	return ret;
}

Game::~Game() {
	SDL_DestroyTexture(this->BgTexture);
	SDL_DestroyTexture(this->ShipsTexture);
	SDL_DestroyTexture(this->BeamTexture);
}

void Game::doCollisions() {
	for (Beam &b : Beam::beams) {
		for (Asteroid &a : Asteroid::asteroids) {
			bool hit = a.intersects(b.points[0]);
			hit = hit || a.intersects(b.points[1]);
			if (hit) {
				b.X = 10000; // move out of bounds
				a.damage();
			}
		}
	}
}

void Game::renderBeams() {
	for (Beam &b : Beam::beams) {
		SDL_Rect dst = b.getDstRect();
		SDL_RenderCopyEx(renderer, BeamTexture, NULL, &dst, (b.rot-M_PI)*-180/M_PI, NULL, SDL_FLIP_NONE);
		b.tick();
	}
}

void Game::renderAsteroids() {
	for (Asteroid &a : Asteroid::asteroids) {
		SDL_Rect src = a.getSrcRect(), dst = a.getDstRect();
		SDL_RenderCopyEx(renderer, AsteroidsTexture, &src, &dst, a.rot, NULL, SDL_FLIP_NONE);
		a.tick();
	}
}

void Game::handleKeyPresses() {
	if(util::isPressed(pressed, SDLK_UP)) {
		VelY += ACCEL_MOD * cos(rotation);
		VelX += ACCEL_MOD * sin(rotation);
	}
	if(util::isPressed(pressed, SDLK_LEFT)) 				{ rotation += STEERING_MOD;	}
	if(util::isPressed(pressed, SDLK_RIGHT)) 				{ rotation -= STEERING_MOD;	}
	if(util::isPressed(pressed, SDLK_SPACE) && BeamCD < 0) { shoot();					}
}

void Game::shoot() {
	Beam::shoot(ShipRect.x+20,ShipRect.y+25,rotation); BeamCD = BEAMCOOLDOWN;
}