#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_keycode.h>
#include "State.hpp"
#include <vector>

namespace AsteroidShooter {
class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer, bool debug);
		int score;
	private:
		SDL_Texture *BgTexture, *ShipsTexture, *BeamTexture, *AsteroidsTexture, *ForceFieldTexture, *MenuTexture, *RestartTexture, *HomeTexture;
		const static SDL_FRect BgRect, ForceFieldSrcRect;
		SDL_Renderer *renderer;
		float BackgroundOffset, animationState;
		int tick;
		bool dead, shouldQuit, paused = false;
		std::vector<SDL_Keycode> pressed;
		void doCollisions();
		void renderBeams(), renderAsteroids(), renderLives(), renderParticles(), renderShip(), renderMenu();
		void handleEvents();
};
}