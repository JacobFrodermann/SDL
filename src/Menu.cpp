#include "Menu.hpp"
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "Util.hpp"

int Menu::init(SDL_Renderer * renderer, bool) {
    SDL_Surface * bg = IMG_Load("assets/actionfieldBg1.png");
    this->BgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);
    bg = IMG_Load("assets/Start.png");
    this->StartTexture = SDL_CreateTextureFromSurface(renderer,bg);
    SDL_FreeSurface(bg);
    return 0;
}

int Menu::draw(SDL_Renderer * renderer) {
    int ret = 0;
    SDL_Rect Rect = {690,0,540,1080};

    SDL_RenderCopy(renderer, BgTexture, NULL,&Rect);
    SDL_RenderCopy(renderer, StartTexture, NULL,&this->StartRect);

    int mouseX = 0, mouseY = 0;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT) {
            ret = SDL_QUIT;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouseX, &mouseY);
            //spdlog::debug("click at [" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + "]");
            SDL_Point p = {mouseX, mouseY};
            if (util::contains(this->StartRect,p)) {
                ret = GAME_STATE;
            }
        }
    }



    return ret;
}
Menu::~Menu() {
    SDL_DestroyTexture(this->BgTexture);
    SDL_DestroyTexture(this->StartTexture);
}