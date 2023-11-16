#include <SDL.h>

class util {
    public:
    static SDL_Rect rect(int x, int y, int w, int h);
    static bool contains(SDL_Rect rect, SDL_Point point);
};