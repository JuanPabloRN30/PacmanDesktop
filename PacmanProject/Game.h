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

	static void addTile(int id, int x, int y);
	static bool isRunning;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static std::vector<ColliderComponent*> colliders;

private:
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 600;
	SDL_Window* window;
};
