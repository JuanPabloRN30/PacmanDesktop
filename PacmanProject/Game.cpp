#include "Game.h"

#include<iostream>
#include <time.h>
#include "SDL_image.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "res_path.h"
#include "cleanup.h"
#include "Map.h"

#include "ECS.h"
#include "Components.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;

bool Game::isRunning = false;

Manager manager;
auto& player(manager.addEntity());


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
	try {
		pacman = new Pacman(pacmanFile.c_str(), 0, 0, iW, iH);
	}
	catch (const char* msg) {
		TextureManager::LogSDLError(std::cout, "Error");
		return false;
	}

	const std::string ghostFile = resPath + "ghosts.png";
	try {
		cyanGhostObj = new CyanGhost(ghostFile.c_str(), 2, 0, iW, iH);
		orangeGhostObj = new OrangeGhost(ghostFile.c_str(), 3, 0, iW, iH);
		pinkGhostObj = new PinkGhost(ghostFile.c_str(), 4, 0, iW, iH);
		redGhostObj = new RedGhost(ghostFile.c_str(), 5, 0, iW, iH);
	}
	catch (const char* msg) {
		TextureManager::LogSDLError(std::cout, "Error");
		return false;
	}
	player.addComponent<PositionComponent>();
	player.getComponent<PositionComponent>().setPos(500, 500);

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
			pacman->setDirection(Pacman::Direction::DOWN);
			break;
		case SDLK_UP:
			pacman->setDirection(Pacman::Direction::UP);
			break;
		case SDLK_LEFT:
			pacman->setDirection(Pacman::Direction::LEFT);
			break;
		case SDLK_RIGHT:
			pacman->setDirection(Pacman::Direction::RIGHT);
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
	manager.update();
	std::cout << player.getComponent<PositionComponent>().x() << "," << player.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	//player.draw();
/*	pacman->draw();
	cyanGhostObj->draw();
	orangeGhostObj->draw();
	pinkGhostObj->draw();
	redGhostObj->draw();*/
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}
