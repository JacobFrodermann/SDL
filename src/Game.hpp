#pragma once
#include "State.hpp"
#include <vector>

class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer);
	private:
		SDL_Texture* BgTexture;
		SDL_Texture* ShipsTexture;
		SDL_Rect BgRect, ShipRect, ShipSrcRect;
		float BgYOffset;
		float VelX, VelY, anim;
		int *X, *Y;
		bool dead;
		std::vector<int> pressed;
};