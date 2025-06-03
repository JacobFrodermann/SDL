#pragma once
#include "SDL_render.h"
#include "State.hpp"
#include <vector>

class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer, bool debug);
		int score;
	private:
		SDL_Texture *BgTexture, *ShipsTexture, *BeamTexture, *AsteroidsTexture, *ForceFieldTexture;
		SDL_Rect BgRect, ForceFieldSrcRect;
		SDL_Renderer *renderer;
		float BackgroundOffset, animationState;
		int tick;
		bool dead;
		std::vector<int> pressed;
		void doCollisions(), renderBeams(), renderAsteroids(), handleKeyPresses();
};