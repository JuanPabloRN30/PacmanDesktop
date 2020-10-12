#include <iostream>
#include "cleanup.h"
#include "Constants.h"
#include "TextureManager.h"
#include "Window.h"

AssetManager* Window::_assets = new AssetManager();
SDL_Event Window::_event;

bool Window::init()
{
	_window = SDL_CreateWindow("Pacman game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_window == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateWindow");
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateRenderer");
		return false;
	}

	_windowID = SDL_GetWindowID(_window);

	return _init();
}

bool Window::isRunning()
{
	return _isRunning;
}

void Window::_clean()
{
}

bool Window::_init() {
	return true;
}

void Window::_handleEvents(SDL_Event& event)
{
}

void Window::handleEvents()
{
	SDL_PollEvent(&_event);

	if (_event.window.windowID == _windowID) {
		_handleEvents(_event);
	}

	//If user closes the window
	if (_event.type == SDL_QUIT) {
		_isRunning = false;
	}

	//If user clicks the mouse
	if (_event.type == SDL_MOUSEBUTTONDOWN) {
		//_isRunning = false;
	}
}

void Window::update()
{
}

void Window::render()
{
}

void Window::clean()
{
	cleanup(_renderer, _window);
	_clean();
}
