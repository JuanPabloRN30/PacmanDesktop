#pragma once

#include <SDL.h>
#include <vector>

class ColliderComponent;


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
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemies,
		groupColliders,
		groupCookies
	};

private:
	SDL_Window* window;
};
