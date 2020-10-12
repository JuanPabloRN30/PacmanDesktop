#include "Game.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "TextureManager.h"
#include "MenuWindow.h"

Window* Game::currentWindow;

Game::Game() {}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		TextureManager::LogSDLError(std::cout, "SDL_Init");
		return false;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		TextureManager::LogSDLError(std::cout, "IMG_Init");
		return false;
	}

	if (TTF_Init() == -1) {
		TextureManager::LogSDLError(std::cout, "TTF_Init");
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		TextureManager::LogSDLError(std::cout, "SDL_Mixer error");
		return false;
	}

	MenuWindow* menu = new MenuWindow();
	currentWindow = menu;
	_scenes.push(menu);
	return menu->init();
}

bool Game::isRunning()
{
	Window* current = getCurrentWindow();
	if (current == nullptr) return false;
	return current->isRunning();
}

void Game::handleEvents()
{
	Window* current = getCurrentWindow();
	if (current == nullptr) return;
	current->handleEvents();
}

void Game::update()
{
	Window* current = getCurrentWindow();
	if (current == nullptr) return;
	current->update();
}

void Game::render()
{
	Window* current = getCurrentWindow();
	if (current == nullptr) return;
	current->render();
}

void Game::clean()
{
	Window* current = getCurrentWindow();
	if (current != nullptr)
		current->clean();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Window* Game::getCurrentWindow()
{
	return currentWindow;
}
