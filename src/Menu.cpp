#include "State.hpp"
#include <SDL.h>
#include <SDL_image.h>

int Menu::init(SDL_Rendere * renderer) {
    SDL_Surface * bg = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);
}

int Menu::draw(SDL_Renderer * renderer) {
    SDL_Rect MenuBgTextureRect = {690,0,540,1080};

    SDL_RenderCopy(renderer, bgTexture, NULL,MenuBgRect);
}