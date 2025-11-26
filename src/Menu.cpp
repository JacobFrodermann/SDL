#include "Menu.hpp"
#include <SDL3/SDL_mouse.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <cstddef>
#include <spdlog/spdlog.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include "Utils/Util.hpp"

namespace AsteroidShooter {
    
int Menu::init(SDL_Renderer * renderer, bool) {
    SDL_Surface *surf = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);

    surf = IMG_Load("assets/Start.png");    
    this->StartTexture = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_DestroySurface(surf);

    surf = IMG_Load("assets/Quit.png");
    this->QuitTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    return 0;
}

int Menu::draw(SDL_Renderer * renderer) {
    frameNum += .1;

    SDL_FRect currentStart = this->StartRect;
    currentStart.y += cos(frameNum) * 4;
    
    SDL_FRect currentQuit = this->QuitRect;
    currentQuit.y -= cos(frameNum*.5) * 5;
    SDL_RenderTexture(renderer, BgTexture, NULL, &this->BgRect);
    SDL_RenderTexture(renderer, StartTexture, NULL, &currentStart);
    SDL_RenderTexture(renderer, QuitTexture, NULL, &currentQuit);
    
    SDL_Event e;
    float mouseX = 0, mouseY = 0;
    int ret = 0;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_EVENT_QUIT) {
            ret = SDL_EVENT_QUIT;
        }
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            SDL_GetMouseState(&mouseX, &mouseY);
            //spdlog::debug("click at [" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + "]");
            SDL_FPoint p = {mouseX, mouseY};
            if (Util::contains(currentStart,p)) {
                ret = GAME_STATE;
            }
            if (Util::contains(currentQuit, p)) {
                return SDL_EVENT_QUIT;
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