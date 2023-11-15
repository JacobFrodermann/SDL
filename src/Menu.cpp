#include "Menu.hpp"
#include <SDL_image.h>
#include <iostream>

int Menu::init(SDL_Renderer * renderer) {
    std::cout << "1" << std::endl;
    SDL_Surface * bg = IMG_Load("assets/actionfieldBg1.png");
    std::cout << "1" << std::endl;
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    std::cout << "1" << std::endl;
    SDL_FreeSurface(bg);
    std::cout << "1" << std::endl;
}

int Menu::draw(SDL_Renderer * renderer) {
    SDL_Rect MenuBgTextureRect = {690,0,540,1080};

    SDL_RenderCopy(renderer, BgTexture, NULL,&MenuBgTextureRect);
}
Menu::~Menu() {
    SDL_DestroyTexture(this->BgTexture);
}