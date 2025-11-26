#pragma once
#if (!SDL)
    #include <SDL3/SDL.h>
#endif
#define MENU_STATE 1
#define GAME_STATE 2


namespace AsteroidShooter {
class State {
    public:
        virtual ~State();
        virtual int draw(SDL_Renderer*);
        virtual int init(SDL_Renderer*, bool);
        bool debug;
};
}
