#include "Game.h"

#include<iostream>
#include <time.h>
#include "SDL_image.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "res_path.h"
#include "cleanup.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;
std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;
auto& pacman(manager.addEntity());
auto& cyanGhost(manager.addEntity());
auto& orangeGhost(manager.addEntity());
auto& pinkGhost(manager.addEntity());
auto& redGhost(manager.addEntity());

auto& wall(manager.addEntity());


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

	int iW = 60, iH = 60;
	const std::string resPath = getResourcePath("PacmanProject");
	const std::string mapFile = resPath + "map.txt";
	const std::string pacmanFile = resPath + "pacmanv3.png";
	const std::string ghostFile = resPath + "ghosts.png";

	Map::loadMap(mapFile, 10, 10);

	// PACMAN
	pacman.addComponent<TransformComponent>();
	pacman.addComponent<SpriteComponent>(pacmanFile.c_str());
	pacman.addComponent<KeyBoardController>();
	pacman.addComponent<ColliderComponent>("player");

	// GHOST
	cyanGhost.addComponent<TransformComponent>(60, 0);
	cyanGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	orangeGhost.addComponent<TransformComponent>(120, 0);
	orangeGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	pinkGhost.addComponent<TransformComponent>(180, 0);
	pinkGhost.addComponent<SpriteComponent>(ghostFile.c_str());
	redGhost.addComponent<TransformComponent>(240, 0);
	redGhost.addComponent<SpriteComponent>(ghostFile.c_str());

	wall.addComponent<TransformComponent>(300, 300, 300, 20, 1);
	wall.addComponent<SpriteComponent>(ghostFile.c_str());
	wall.addComponent<ColliderComponent>("wall");

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

	//If user clicks the mouse
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		isRunning = false;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto& cc : colliders) {
		Collision::AABB(pacman.getComponent<ColliderComponent>(), *cc);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 60, 60, id);

}
