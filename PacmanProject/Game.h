#pragma once

#include <SDL.h>
#include <vector>

class AssetManager;
class ColliderComponent;
class SoundManager;


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

	void saveScore();
	void loadHighestScore();

	static int highScore;
	static int level;
	static const char* scoreFilePath;
	static bool isRunning;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static AssetManager* assets;
	static SoundManager* sounds;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemies,
		groupColliders,
		groupCookies,
		groupPowerCookies,
		groupLabels
	};

private:
	SDL_Window* window;
};
