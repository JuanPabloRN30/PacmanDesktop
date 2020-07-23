#pragma once

#include <SDL.h>
#include "Pacman.h"
#include "CyanGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include "RedGhost.h"


class Game
{
public:

	Game();

	bool init();
	void handleEvents();
	void update();
	bool running();
	void render();
	void clean();

	static bool isRunning;
	static SDL_Event event;
	static SDL_Renderer* renderer;

private:
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 600;
	SDL_Window* window;
};
