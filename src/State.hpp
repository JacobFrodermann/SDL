#include <SDL.h>

class State {
    public:
        virtual ~State() = default;
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer);
};

class Menu : public State {  
    public:
        virtual ~Menu() = default;
        int draw(SDL_Renderer* renderer);
        int init(SDL_Renderer* renderer);
    private:
        SDL_Texture* BgTexture;
};