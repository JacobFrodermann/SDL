#pragma once
#include "SDL_render.h"
#include "State.hpp"
#include <vector>

class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer);
	private:
		SDL_Texture *BgTexture, *ShipsTexture, *BeamTexture, *AsteroidsTexture;
		SDL_Rect BgRect, ShipRect, ShipSrcRect;
		SDL_Renderer *renderer;
		float BackgroundOffset, VelX, VelY, animationState, rotation,X,Y;
		int BeamCD, tick;
		bool dead;
		std::vector<int> pressed;
		void doCollisions(), renderBeams(), renderAsteroids(), handleKeyPresses(), shoot();
};