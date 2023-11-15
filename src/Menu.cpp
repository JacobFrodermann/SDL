#include "State.hpp"
#include <SDL.h>
#include <SDL_image.h>

int Menu::init(SDL_Rendere * renderer) {
    SDL_Surface * bg = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, bg);
}

bool Menu::draw(SDL_Renderer * renderer) {

}