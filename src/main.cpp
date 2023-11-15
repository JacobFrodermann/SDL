#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include "InitError.hpp"
#include "Util.hpp"
#include <SDL_image.h>
#include "Menu.hpp"
#include <memory>

class SDL {
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
public:
	SDL(Uint32 flags = 0);
	virtual ~SDL();
	void draw();
};

SDL::SDL(Uint32 flags) {
	if (SDL_Init(flags) != 0)throw InitError();

	if (SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_SHOWN, &m_window, &m_renderer) != 0) throw InitError();

    SDL_SetWindowFullscreen(m_window, true);
    SDL_ShowCursor(true);

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
	
}

SDL::~SDL() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void SDL::draw() {
	
	SDL_Surface * bg = IMG_Load("assets/MainBg.png");
	SDL_Texture * bgTexture = SDL_CreateTextureFromSurface(m_renderer, bg);

	bool quit =	false;

	std::unique_ptr<State> state = std::make_unique<Menu>();
	state->init(m_renderer);
	std::cout << "2" << std::endl;
	
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT) {
				SDL_Quit();
				quit = true;
			}
		}


		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		SDL_RenderCopy(m_renderer, bgTexture, NULL,NULL);

		//int todo = state->draw(m_renderer);

		SDL_RenderPresent(m_renderer);
		
		SDL_Delay(60);
	}
}

int main(int argc, char* argv[]) {
	try {
		SDL sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		sdl.draw();

		return 0;
	}
	catch (const InitError& err) {
		std::cerr << "Error while initializing SDL:  "
			<< err.what()
			<< std::endl;
	}

	return 1;
}
