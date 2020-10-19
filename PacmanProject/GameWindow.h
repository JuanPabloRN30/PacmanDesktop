#pragma once
#include "Window.h"
class GameWindow : public Window
{
public:
	void _clean() override;

	bool _init() override;

	void _handleEvents(SDL_Event& event) override;

	void update() override;


	void render() override;

	enum groupLabels : std::size_t {
		groupColliders,
		groupCookies,
		groupEnemies,
		groupLabels,
		groupMap,
		groupPlayer,
		groupPowerCookies
	};

private:

	void saveScore();
	void loadHighestScore();
	int highScore;
};

