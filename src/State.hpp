#include <SDL.h>

class State {
    public:
        virtual bool draw(SDL_Renderer* m_renderer);
        virtual int  init(SDL_Renderer* m_renderer);
};

class Menu : public State {
    public:
        bool draw(SDL_Renderer* m_renderer);
        int init(SDL_Renderer* renderer);
    private:
        SDL_Texture* BgTexture;
};