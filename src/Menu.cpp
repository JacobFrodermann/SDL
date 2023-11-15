#include "Menu.hpp"
#include <SDL_image.h>
#include <iostream>

int Menu::init(SDL_Renderer * renderer) {
    SDL_Surface * bg = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);
    return 0;
}

int Menu::draw(SDL_Renderer * renderer) {
    int ret = 0;
    SDL_Rect MenuBgTextureRect = {690,0,540,1080};

    SDL_RenderCopy(renderer, BgTexture, NULL,&MenuBgTextureRect);


    SDL_Event e;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT) {
            ret = SDL_QUIT;
        }
        if (e.type == SDL_MouseButtonEvent) {
            
        }
    }



    return ret;
}
Menu::~Menu() {
    SDL_DestroyTexture(this->BgTexture);
}