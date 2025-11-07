#include <cstdio>
#include <cstring>
#include <iostream>
#include <SDL.h>
#include "Utils/InitError.hpp"
#include <SDL_image.h>
#include "Menu.hpp"
#include <memory>
#include "Game.hpp"
#include <chrono>
#include <ostream>
#include <spdlog/common.h>
#include <string>
#include "Settings.hpp"
#include "spdlog/spdlog.h"

class SDL {
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
public:
	SDL(Uint32 flags = 0);
	virtual ~SDL();
	void draw();
	bool debug = false;
};

SDL::SDL(Uint32 flags) {
	if (SDL_Init(flags) != 0)throw InitError();

	if (SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_SHOWN, &m_window, &m_renderer) != 0) throw InitError();

    //SDL_SetWindowFullscreen(m_window, true);
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
	SDL_Surface * bg = IMG_Load("assets/MainBg.png");
	SDL_Texture * bgTexture = SDL_CreateTextureFromSurface(m_renderer, bg);

	bool quit =	false;
	int stateCode = MENU_STATE;

	std::shared_ptr<State> state = std::make_shared<Menu>();
	state->init(m_renderer, debug);

	std::shared_ptr<State> game = std::make_shared<Game>();
	game->init(m_renderer, debug);

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
			spdlog::info("Started Game");
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
		int passed = std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
		spdlog::info("render took " + std::to_string(passed) + "ms");
		
		int wait = 1000/FRAMERATE - passed; 
		SDL_Delay((wait < 0) ? 0 : wait);
	}
}

int main(int argc, char* argv[]) {
	spdlog::info("Starting AsteroidShooter");
	
	bool debug = false;
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << " ";
		if (strcmp(argv[i], "--debug") == 0) {
			spdlog::info("Debug Mode");
			spdlog::set_level(spdlog::level::trace);
			debug = true;
		}
	}
	std::cout << std::endl;


	try {
		SDL sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		sdl.debug = debug;
		sdl.draw();

		return 0;
	}
	catch (const InitError& err) {
		spdlog::error("Error while initializing SDL: " + std::string(err.what()));
	}

	return 1;
}
