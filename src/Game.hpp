#if (!State)
	#include "State.hpp"
#endif

class Game : public State {  
	public:
		virtual ~Game();
		virtual int draw(SDL_Renderer* renderer);
		virtual int init(SDL_Renderer* renderer);
	private:
		SDL_Texture* BgTexture;
		SDL_Texture* ShipsTexture;
		SDL_Rect BgRect;
};