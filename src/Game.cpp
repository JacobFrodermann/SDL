#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

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
	X = &ShipRect.x;
	Y = &ShipRect.y;
	anim = 0;
	dead = false;
	ShipSrcRect = {0,0,40,60};
	pressed = {};
	return 0;
}

int Game::draw(SDL_Renderer * renderer) {
	int ret = 0;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT) {
			ret = SDL_QUIT;
		} else if (e.type == SDL_KEYDOWN) {
			pressed.push_back(e.key);
		} else if (e.type == SDL_KEYUP) {
		{
			pressed.erase(std::remove(pressed.begin(), pressed.end(), e.key), pressed.end());
		}
		
		
	}
	
	BgYOffset -= .1f;
	anim += .05f;
	if ((int) anim == 4) anim = 0; //reset animation before 5

	ShipSrcRect.y = (int) anim * 60; 

	this->BgRect.y = (int) BgYOffset;


	SDL_RenderCopy(renderer, BgTexture, NULL, &BgRect);
	SDL_RenderCopy(renderer, ShipsTexture, &ShipSrcRect, &ShipRect);

	return ret;
}

Game::~Game() {
	SDL_DestroyTexture(this->BgTexture);
	SDL_DestroyTexture(this->ShipsTexture);
}


