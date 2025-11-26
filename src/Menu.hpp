#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "State.hpp"

namespace AsteroidShooter {
class Menu : public State {  
    public:
        virtual ~Menu();
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer, bool debug);
    private:
        SDL_Texture* BgTexture;
        SDL_Texture* StartTexture;
        SDL_Texture* QuitTexture;

        constexpr static SDL_FRect BgRect = {690,0,540,1080};
        constexpr static SDL_FRect StartRect = {140+690,363,256,87};
        constexpr static SDL_FRect QuitRect = {160+690,800,150,87};
        
        double frameNum = 0;
};
}