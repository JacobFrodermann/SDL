#include <SDL.h>

class State {
    public:
        virtual ~State();
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer);
};

