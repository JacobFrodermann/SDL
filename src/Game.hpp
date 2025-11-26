#pragma once
#include <SDL3/SDL_render.h>
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
		SDL_Texture *BgTexture, *ShipsTexture, *BeamTexture, *AsteroidsTexture, *ForceFieldTexture;
		const static SDL_FRect BgRect, ForceFieldSrcRect;
		SDL_Renderer *renderer;
		float BackgroundOffset, animationState;
		int tick;
		bool dead;
		std::vector<int> pressed;
		void doCollisions(), renderBeams(), renderAsteroids(), renderLives(), renderParticles(), handleKeyPresses();
};
}