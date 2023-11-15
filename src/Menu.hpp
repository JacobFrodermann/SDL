#include "State.hpp"

class Menu : public State {
    public:
        bool draw(SDL_Renderer* m_renderer);
        int init(SDL_Renderer* renderer);
        Menu();
    private:
        SDL_Texture* BgTexture;
};