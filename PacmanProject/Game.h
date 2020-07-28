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

	static void addTile(int srcX, int srcY, int xpos, int ypos);
	static bool isRunning;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static std::vector<ColliderComponent*> colliders;
	static const int SCREEN_WIDTH = 600;
	static const int SCREEN_HEIGHT = 600;

private:
	SDL_Window* window;
};
