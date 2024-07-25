#pragma once
#include "State.hpp"
#include <vector>

class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer);
	private:
		SDL_Texture *BgTexture, *ShipsTexture, *BeamTexture;
		SDL_Rect BgRect, ShipRect, ShipSrcRect;
		float BackgroundOffset;
		float VelX, VelY, animationState, rotation,X,Y;
		int BeamCD;
		bool dead;
		std::vector<int> pressed;
};