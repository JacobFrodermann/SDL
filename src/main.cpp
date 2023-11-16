#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include "InitError.hpp"
#include "Util.hpp"
#include <SDL_image.h>
#include "Menu.hpp"
#include <memory>
#include "Game.hpp"
#include <chrono>

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
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );

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
	auto now = std::chrono::high_resolution_clock::now();
	SDL_Surface * bg = IMG_Load("assets/MainBg.png");
	SDL_Texture * bgTexture = SDL_CreateTextureFromSurface(m_renderer, bg);

	bool quit =	false;
	int stateCode = MENU_STATE;

	std::shared_ptr<State> state = std::make_shared<Menu>();
	state->init(m_renderer);

	std::shared_ptr<State> game = std::make_shared<Game>();
	game->init(m_renderer);

	std::shared_ptr<State> menu;

	
	while (!quit) {
		auto then = std::chrono::high_resolution_clock::now();
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		SDL_RenderCopy(m_renderer, bgTexture, NULL,NULL);

		int todo = state->draw(m_renderer);

		switch (todo) {
		case SDL_QUIT:
			quit = true;
            SDL_Quit();
			break;
		case GAME_STATE:
			std::cout << "Game" << std::endl;
			if (stateCode == MENU_STATE) {
				state.swap(game);
				game.swap(menu);
			}
			stateCode = GAME_STATE;
			
		default:
			break;
		}

		SDL_RenderPresent(m_renderer);

		auto now = std::chrono::system_clock::now();		
		int passed = 1000/40 - std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
		SDL_Delay((passed < 0) ? 0 : passed);
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
