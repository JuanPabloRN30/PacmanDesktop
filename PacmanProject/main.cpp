#include <stack>
#include "Game.h"


int main(int, char**) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = new Game();
	Window::_assets = new AssetManager();

	if (game->init() == false) {
		return -1;
	}

	while (game->isRunning()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();

	return 0;
}
