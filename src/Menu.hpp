#include "State.hpp"

class Menu : public State {  
    public:
        virtual ~Menu();
        virtual int draw(SDL_Renderer* renderer);
        virtual int init(SDL_Renderer* renderer);
    private:
        SDL_Texture* BgTexture;
        SDL_Texture* StartTexture;
        SDL_Rect StartRect = {140+690,363,256,87};
};