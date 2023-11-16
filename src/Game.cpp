#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>

int Game::init(SDL_Renderer * renderer) {
    SDL_Surface * surface = IMG_Load("assets/GameBG.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Ships.png");
    this->ShipsTexture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    this->BgRect = {690,0,540,2160}
    return 0;
}

int Game::draw(SDL_Renderer * renderer) {
    SDL_RenderCopy(renderer, this->BgTexture, NUll, &this->BgRect)
    return 0;
}


