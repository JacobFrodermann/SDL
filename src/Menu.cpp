#include "Menu.hpp"
#include <SDL_image.h>
#include <cmath>
#include <cstddef>
#include <spdlog/spdlog.h>
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "Utils/Util.hpp"

namespace AsteroidShooter {
int Menu::init(SDL_Renderer * renderer, bool) {
    SDL_Surface * surf = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    surf = IMG_Load("assets/Start.png");    
    this->StartTexture = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_FreeSurface(surf);

    surf = IMG_Load("assets/Quit.png");
    this->QuitTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return 0;
}

int Menu::draw(SDL_Renderer * renderer) {
    frameNum += .1;

    SDL_Rect currentStart = this->StartRect;
    currentStart.y += cos(frameNum) * 4;
    
    SDL_Rect currentQuit = this->QuitRect;
    currentQuit.y -= cos(frameNum*.5) * 5;
    
    SDL_RenderCopy(renderer, BgTexture, NULL,&this->BgRect);
    SDL_RenderCopy(renderer, StartTexture, NULL,&currentStart);
    SDL_RenderCopy(renderer, QuitTexture, NULL, &currentQuit);
    
    SDL_Event e;
    int mouseX = 0, mouseY = 0, ret = 0;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT) {
            ret = SDL_QUIT;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouseX, &mouseY);
            //spdlog::debug("click at [" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + "]");
            SDL_Point p = {mouseX, mouseY};
            if (util::contains(currentStart,p)) {
                ret = GAME_STATE;
            }
            if (util::contains(currentQuit, p)) {
                return SDL_QUIT;
            }
        }
    }



    return ret;
}

Menu::~Menu() {
    SDL_DestroyTexture(this->BgTexture);
    SDL_DestroyTexture(this->StartTexture);
    SDL_DestroyTexture(this->QuitTexture);
}
}