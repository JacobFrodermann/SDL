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
#include "Ship.hpp"
#include "Util.hpp"
#include "Beam.hpp"
#include "Asteroid.hpp"

int Game::init(SDL_Renderer * renderer) {
	this->BgTexture = util::loadTexuture("assets/GameBG.png", renderer);
	this->ShipsTexture = util::loadTexuture("assets/Ships.png", renderer);
	this->BeamTexture = util::loadTexuture("assets/beam.png",renderer);
	this->AsteroidsTexture = util::loadTexuture("assets/asteriodAtlas.png", renderer);
	this->ForceFieldTexture = util::loadTexuture("assets/forcefield.png", renderer);


	this->BgRect = {690,0,540,2160};
	this->ForceFieldSrcRect = {0,0,50,70};

	BackgroundOffset = 0;
	animationState = 0;
	dead = false;
	pressed = {};
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

	if (!Ship::player.dead) {	
		Ship::player.tick();
		Asteroid::spawn(score);
		doCollisions();

		if (tick == 1) {
			Beam::filter();
			Asteroid::filter();
			score ++;
		}

		Asteroid::tick();

	}
	
	BackgroundOffset -= .1f;
	animationState += .05f;

	if ((int) animationState == 4) animationState = 0; //reset animation before 5

	renderAsteroids();

	renderBeams();

	SDL_RenderCopyEx(renderer, ShipsTexture, Ship::player.getSrcRect(animationState), Ship::player.getDstRect(),(Ship::player.rotation-M_PI)*-180/M_PI,NULL,SDL_FLIP_NONE);
	if (Ship::player.isInvis()) {
		SDL_RenderCopyEx(renderer, ForceFieldTexture, &ForceFieldSrcRect, Ship::player.getDstRect(),(Ship::player.rotation-M_PI)*-180/M_PI,NULL,SDL_FLIP_NONE);
	}
	

	return ret;
}

Game::~Game() {
	SDL_DestroyTexture(this->BgTexture			);
	SDL_DestroyTexture(this->ShipsTexture		);
	SDL_DestroyTexture(this->BeamTexture		);
	SDL_DestroyTexture(this->AsteroidsTexture	);
}

void Game::doCollisions() {
	for (Beam &b : Beam::beams) {
		for (Asteroid &a : Asteroid::asteroids) {
			bool hit = a.intersects(b.points[0]);
			hit = hit || a.intersects(b.points[1]);
			if (hit) {
				b.removeMe = true;
				b.X = 1000000; // move out of bounds
				a.damage();
			}
		}
	}
	bool hit = false;
	for (Asteroid &a : Asteroid::asteroids) {
		if (a.intersects(Ship::player.getColRect())) {
			hit = true;
			break;
		}
	}
	if (hit) {
		Ship::player.damage(1);
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
		SDL_RenderDrawRect(renderer,&dst);
		SDL_RenderCopyEx(renderer, AsteroidsTexture, &src, &dst, a.rot, NULL, SDL_FLIP_NONE);
	}
}

void Game::handleKeyPresses() {
	if(util::isPressed(pressed, SDLK_UP)) {
		Ship::player.accel(ACCEL_MOD);
	}
	if(util::isPressed(pressed, SDLK_LEFT))  { Ship::player.rot(STEERING_MOD);	}
	if(util::isPressed(pressed, SDLK_RIGHT)) { Ship::player.rot(-STEERING_MOD);}
	if(util::isPressed(pressed, SDLK_SPACE)) { Ship::player.shoot();			}
}
