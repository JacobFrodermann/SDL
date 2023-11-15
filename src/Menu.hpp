#include "State.hpp"

class Menu : public State {  
    public:
        virtual ~Menu();
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer);
    private:
        SDL_Texture* BgTexture;
};