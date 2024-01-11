#include "Game.hpp"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include "Settings.hpp"

int Game::init(SDL_Renderer * renderer) {
	SDL_Surface * surface = IMG_Load("assets/GameBG.png");
	this->BgTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("assets/Ships.png");
	this->ShipsTexture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	this->BgRect = {690,0,540,2160};
	BgYOffset = 0;
	VelX = 0;
	VelY = 0;
	ShipRect = {920,900,60,90};
	X = ShipRect.x;
	Y = ShipRect.y;
	anim = 0;
	dead = false;
	ShipSrcRect = {0,0,40,60};
	pressed = {};
	rot = M_PI;
	return 0;
}

int Game::draw(SDL_Renderer * renderer) {
	int ret = 0;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT) {
			ret = SDL_QUIT;
		} else if (e.type == SDL_KEYDOWN) {
			pressed.push_back(e.key.keysym.sym);
		} else if (e.type == SDL_KEYUP) {
			pressed.erase(std::remove(pressed.begin(), pressed.end(), e.key.keysym.sym), pressed.end());
		}
	}

	if(std::find(pressed.begin(), pressed.end(), SDLK_UP) != pressed.end()) {
		VelY += ACCEL_MOD * cos(rot);
		VelX += ACCEL_MOD * sin(rot);
	}
	if(std::find(pressed.begin(), pressed.end(), SDLK_LEFT ) != pressed.end()) {rot += STEERING_MOD;}
	if(std::find(pressed.begin(), pressed.end(), SDLK_RIGHT) != pressed.end()) {rot -= STEERING_MOD;}
	X += VelX/1.5;
	Y += VelY/1.5;
	VelX = VelX / FRICTION_MOD;
	VelY = VelY / FRICTION_MOD;


	ShipRect.x = X;
	ShipRect.y = Y;

	BgYOffset -= .1f;
	anim += .05f;
	if ((int) anim == 4) anim = 0; //reset animation before 5

	ShipSrcRect.y = (int) anim * 60; //move Rect to fitting image

	this->BgRect.y = (int) BgYOffset;

	SDL_RenderCopy(renderer, BgTexture, NULL, &BgRect);
	SDL_RenderCopyEx(renderer, ShipsTexture, &ShipSrcRect, &ShipRect,(rot-M_PI)*-180/M_PI,NULL,SDL_FLIP_NONE);

	return ret;
	
}

Game::~Game() {
	SDL_DestroyTexture(this->BgTexture);
	SDL_DestroyTexture(this->ShipsTexture);
}
