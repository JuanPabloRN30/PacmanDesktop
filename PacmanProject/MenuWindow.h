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
		groupFooters
	};

	static SDL_Event _menuEvent;

private:
	int sectionHeight = Constants::SCREEN_HEIGHT / 3;
	SDL_Rect titleViewport = { 0, 0, Constants::SCREEN_WIDTH, sectionHeight };
	SDL_Rect optionViewport = { 0, sectionHeight, Constants::SCREEN_WIDTH, sectionHeight };
	SDL_Rect footerViewport = { 0, sectionHeight * 2, Constants::SCREEN_WIDTH, sectionHeight };
};
