#include "Game.h"

#include<iostream>
#include <time.h>
#include "SDL_image.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "res_path.h"
#include "cleanup.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;

bool Game::isRunning = false;

Manager manager;
auto& pacman(manager.addEntity());
auto& cyanGhost(manager.addEntity());
auto& orangeGhost(manager.addEntity());
auto& pinkGhost(manager.addEntity());
auto& redGhost(manager.addEntity());


Game::Game() {}

bool Game::init()
{
	srand(time(nullptr));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		TextureManager::LogSDLError(std::cout, "SDL_Init");
		return false;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		TextureManager::LogSDLError(std::cout, "IMG_Init");
		return false;
	}

	isRunning = true;

	window = SDL_CreateWindow("Pacman game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateWindow");
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateRenderer");
		return false;
	}

	const std::string resPath = getResourcePath("PacmanProject");
	try {
		map = new Map(resPath, 10 * 60, 10 * 60);
	}
	catch (const char* msg) {
		TextureManager::LogSDLError(std::cout, "Error");
		return false;
	}

	int iW = 60, iH = 60;
	const std::string pacmanFile = resPath + "pacmanv3.png";
	const std::string ghostFile = resPath + "ghosts.png";

	// PACMAN
	pacman.addComponent<PositionComponent>();
	pacman.addComponent<SpriteComponent>(pacmanFile.c_str());

	// GHOST
	cyanGhost.addComponent<PositionComponent>(33, 0);
	cyanGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	orangeGhost.addComponent<PositionComponent>(66, 0);
	orangeGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	pinkGhost.addComponent<PositionComponent>(99, 0);
	pinkGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	redGhost.addComponent<PositionComponent>(125, 0);
	redGhost.addComponent<SpriteComponent>(ghostFile.c_str());

	return true;
}

bool Game::running()
{
	return isRunning;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	//If user closes the window
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}
	//If user presses any key
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			//pacman->setDirection(Pacman::Direction::DOWN);
			break;
		case SDLK_UP:
			//pacman->setDirection(Pacman::Direction::UP);
			break;
		case SDLK_LEFT:
			//pacman->setDirection(Pacman::Direction::LEFT);
			break;
		case SDLK_RIGHT:
			//pacman->setDirection(Pacman::Direction::RIGHT);
			break;
		}
	}
	//If user clicks the mouse
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		isRunning = false;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}
