#pragma once

#include <SDL.h>
#include <stack>
#include <vector>
#include "Window.h"

class AssetManager;
class ColliderComponent;
class SoundManager;


class Game
{
public:

	Game();


	bool init();
	bool isRunning();
	void handleEvents();
	void update();
	void render();
	void clean();

	Window* getCurrentWindow();
	static Window* currentWindow;
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
	std::stack<Window*> _scenes;
};
