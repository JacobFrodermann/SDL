#include "Game.hpp"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <vector>
#include "SDL_surface.h"
#include "Settings.hpp"
#include "Util.hpp"
#include "Beam.hpp"
#include <iostream>
#include "Asteroid.hpp"

int Game::init(SDL_Renderer * renderer) {
	SDL_Surface * surface = IMG_Load("assets/GameBG.png");
	this->BgTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("assets/Ships.png");
	this->ShipsTexture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("assets/beam.png");
	this->BeamTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("assets/asteriodAtlas.png");
	this->AsteroidsTexture = SDL_CreateTextureFromSurface(renderer, surface);


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

int Game::draw(SDL_Renderer * renderer) {
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

	if(util::isPressed(pressed, SDLK_UP)) {
		VelY += ACCEL_MOD * cos(rotation);
		VelX += ACCEL_MOD * sin(rotation);
	}
	if(util::isPressed(pressed, SDLK_LEFT)) {rotation += STEERING_MOD;}
	if(util::isPressed(pressed,SDLK_RIGHT)) {rotation -= STEERING_MOD;}
	if(util::isPressed(pressed, SDLK_SPACE) && BeamCD < 0) {Beam::shoot(ShipRect.x+20,ShipRect.y+25,rotation); BeamCD = BEAMCOOLDOWN; Beam::filter();}
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



	//this->BgRect.y = (int) BackgroundOffset;

	//SDL_RenderCopy(renderer, BgTexture, NULL, &BgRect);
	Asteroid::spawn();
	for (Asteroid &a : Asteroid::asteroids) {
		SDL_Rect src = a.getSrcRect(), dst = a.getDstRect();
		//std::cout << "Asteroid at (" << a.X << "," << a.Y << ")" << std::endl; 
		SDL_RenderCopyEx(renderer, AsteroidsTexture, &src, &dst, a.rot, NULL, SDL_FLIP_NONE);
		a.tick();
	}

	for (Beam &b : Beam::beams) {
		SDL_Rect dst = b.getDstRect();
		SDL_RenderCopyEx(renderer, BeamTexture, NULL, &dst, (b.rot-M_PI)*-180/M_PI, NULL, SDL_FLIP_NONE);
		b.tick();
	}

	SDL_RenderCopyEx(renderer, ShipsTexture, &ShipSrcRect, &ShipRect,(rotation-M_PI)*-180/M_PI,NULL,SDL_FLIP_NONE);

	return ret;
}

Game::~Game() {
	SDL_DestroyTexture(this->BgTexture);
	SDL_DestroyTexture(this->ShipsTexture);
	SDL_DestroyTexture(this->BeamTexture);
}
