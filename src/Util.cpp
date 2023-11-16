#include <SDL.h>
#include "Util.hpp"

SDL_Rect util::rect(int x, int y, int w, int h) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;    
}
bool util::contains(SDL_Rect rect, SDL_Point point) {
    return rect.x <= point.x && rect.x+rect.w >= point.x && rect.y <= point.y && rect.y+rect.h >= point.y;
}