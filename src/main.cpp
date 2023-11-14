#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include "InitError.h"


class SDL {
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
public:
	SDL(Uint32 flags = 0);
	virtual ~SDL();
	void draw();
};

SDL::SDL(Uint32 flags) {
	if (SDL_Init(flags) != 0)
		throw InitError();

	if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN,
		&m_window, &m_renderer) != 0)
		throw InitError();
}

SDL::~SDL() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void SDL::draw() {
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);

	// Show the window
	SDL_RenderPresent(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);

	SDL_Rect line;
	line.x=30;
	line.w=580;
	line.h=4;
	line.y=30;

	SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
	
	SDL_RenderFillRect(m_renderer, &line);

	line.y=450;

	SDL_RenderFillRect(m_renderer, &line);

	line.h=424;
	line.y=30;
	line.w=4;

	SDL_RenderFillRect(m_renderer, &line);

	line.x=610;

	SDL_RenderFillRect(m_renderer, &line);

	SDL_RenderPresent(m_renderer);

	SDL_Delay(5000);
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
