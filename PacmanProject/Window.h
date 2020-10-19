#pragma once

#include <SDL.h>
#include "AssetManager.h"

class Window
{
public:
	Window() {}

	bool init();
	bool isRunning();
	void handleEvents();
	void clean();

	virtual void _clean();
	virtual bool _init();
	virtual void _handleEvents(SDL_Event& event);

	virtual void update();
	virtual void render();

	static AssetManager* _assets;
	static SDL_Event _event;
	SDL_Renderer* _renderer;

protected:
	SDL_Window* _window;
	int _windowID;
	bool _isRunning;

};
