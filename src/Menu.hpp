#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include "State.hpp"

class Menu : public State {  
    public:
        virtual ~Menu();
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer, bool debug);
    private:
        SDL_Texture* BgTexture;
        SDL_Texture* StartTexture;
        SDL_Texture* QuitTexture;

        constexpr static SDL_Rect BgRect = {690,0,540,1080};
        constexpr static SDL_Rect StartRect = {140+690,363,256,87};
        constexpr static SDL_Rect QuitRect = {160+690,800,150,87};
        
        double frameNum = 0;
};