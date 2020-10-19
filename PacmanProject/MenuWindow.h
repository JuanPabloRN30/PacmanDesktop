#pragma once
#include "Window.h"
#include "SDL.h"

class MenuWindow : public Window
{
public:
	void _clean() override;

	bool _init() override;

	void _handleEvents(SDL_Event &event) override;

	void update() override;

	
	void render() override;

	enum groups : std::size_t {
		groupTitles,
		groupOptions,
		groupPlayers,
		groupEnemies
	};

	static SDL_Event _menuEvent;

private:
	int waitAnimationMiliseconds = 5000;
	bool buttonPressed = false;
	SDL_Rect titleViewport = { 0, 0, Constants::SCREEN_WIDTH, static_cast<int>(Constants::SCREEN_HEIGHT * .2) };
	SDL_Rect optionViewport = { 0, static_cast<int>(Constants::SCREEN_HEIGHT * .2), Constants::SCREEN_WIDTH, static_cast<int>(Constants::SCREEN_HEIGHT * .6) };
	SDL_Rect footerViewport = { 0, static_cast<int>(Constants::SCREEN_HEIGHT * .8), Constants::SCREEN_WIDTH, static_cast<int>(Constants::SCREEN_HEIGHT * .2) };
};
