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
#include "AssetManager.h"
#include <sstream>
#include <fstream>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;

bool Game::isRunning = false;
int Game::highScore;
const char* Game::scoreFilePath = "scores.txt";

Manager manager;
auto& pacman(manager.addEntity());
auto& cyanGhost(manager.addEntity());
auto& orangeGhost(manager.addEntity());
auto& pinkGhost(manager.addEntity());
auto& redGhost(manager.addEntity());

AssetManager* Game::assets = new AssetManager();

auto& label(manager.addEntity());
auto& highScoreLabel(manager.addEntity());


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

	if (TTF_Init() == -1) {
		TextureManager::LogSDLError(std::cout, "TTF_Init");
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

	assets->addFont("arial", "arial.ttf", 16);

	int iW = 60, iH = 60;
	const std::string resPath = getResourcePath("PacmanProject");
	const std::string pacmanFile = resPath + "pacmanv3.png";

	map = new Map("pacmanboardv2.png", 4, 16);
	map->loadMap("map.map", 13, 7);

	// PACMAN
	pacman.addComponent<TransformComponent>(65, 65);
	pacman.addComponent<SpriteComponent>(pacmanFile.c_str(), true);
	pacman.addComponent<KeyBoardController>();
	pacman.addComponent<ColliderComponent>("player");
	pacman.addComponent<ScoreComponent>();
	pacman.addComponent<LifeComponent>(pacmanFile.c_str());
	pacman.addGroup(groupPlayer);

	// GHOST
	cyanGhost.addComponent<TransformComponent>(60, 0);
	cyanGhost.addComponent<GhostSpriteComponent>("cyan_ghost.png", true);
	cyanGhost.addComponent<RandomMovementComponent>();
	cyanGhost.addComponent<ColliderComponent>("enemy");
	cyanGhost.addComponent<ScoreComponent>(200);
	cyanGhost.addGroup(groupEnemies);
	
	orangeGhost.addComponent<TransformComponent>(120, 0);
	orangeGhost.addComponent<GhostSpriteComponent>("orange_ghost.png", true);
	orangeGhost.addComponent<RandomMovementComponent>();
	orangeGhost.addComponent<ColliderComponent>("enemy");
	orangeGhost.addComponent<ScoreComponent>(200);
	orangeGhost.addGroup(groupEnemies);
	
	pinkGhost.addComponent<TransformComponent>(180, 0);
	pinkGhost.addComponent<GhostSpriteComponent>("pink_ghost.png", true);
	pinkGhost.addComponent<RandomMovementComponent>();
	pinkGhost.addComponent<ColliderComponent>("enemy");
	pinkGhost.addComponent<ScoreComponent>(200);
	pinkGhost.addGroup(groupEnemies);

	redGhost.addComponent<TransformComponent>(240, 0);
	redGhost.addComponent<GhostSpriteComponent>("red_ghost.png", true);
	redGhost.addComponent<RandomMovementComponent>();
	redGhost.addComponent<ColliderComponent>("enemy");
	redGhost.addComponent<ScoreComponent>(200);
	redGhost.addGroup(groupEnemies);

	SDL_Color white = { 255, 255, 255, 255 };
	std::stringstream ss;
	std::stringstream ss1;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.addComponent<UILabel>(Game::SCREEN_WIDTH / 4, 0, ss.str().c_str(), "arial", white);
	label.addGroup(groupLabels);

	loadHighestScore();
	ss1 << "High score: " << highScore;
	highScoreLabel.addComponent<UILabel>(Game::SCREEN_WIDTH / 2, 0, ss1.str().c_str(), "arial", white);
	highScoreLabel.addGroup(groupLabels);

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

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& cookies(manager.getGroup(Game::groupCookies));
auto& powerCookies(manager.getGroup(Game::groupPowerCookies));
auto& labels(manager.getGroup(Game::groupLabels));

void Game::update()
{
	Vector2D pacmanPos = pacman.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.getComponent<UILabel>().setLabelText(ss.str().c_str());

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			pacman.getComponent<TransformComponent>().position = pacmanPos;
		}
	}

	for (auto& c : cookies) {
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			pacman.getComponent<ScoreComponent>().addEntityScore(c->getComponent<ScoreComponent>().score);
			c->destroy();
		}
	}

	for (auto& pc : powerCookies) {
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), pc->getComponent<ColliderComponent>())) {
			for (auto& e : enemies) {
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::scared);
			}
			pc->destroy();
		}
	}

	for (auto& e : enemies) {
		// check collision with enemies
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), e->getComponent<ColliderComponent>())) {
			if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::scared) {
				e->getComponent<TransformComponent>().reset();
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::move);
				pacman.getComponent<ScoreComponent>().addEntityScore(e->getComponent<ScoreComponent>().score);
				for (auto& e : enemies) {
					e->getComponent<ScoreComponent>().setScore(e->getComponent<ScoreComponent>().score * 2);
				}
			}
			else {
				pacman.getComponent<LifeComponent>().loseLife();
				pacman.getComponent<TransformComponent>().reset();
				for (auto& e : enemies) {
					e->getComponent<TransformComponent>().reset();
				}
			}
		}

		if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::move) {
			e->getComponent<ScoreComponent>().setScore(200);
		}
	}

	if (!pacman.getComponent<LifeComponent>().isAlive()) {
		isRunning = false;
		saveScore();
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& l : labels) l->draw();
	for (auto& t : tiles) t->draw();
	//for (auto& c : colliders) c->draw();
	for (auto& c : cookies) c->draw();
	for (auto& pc : powerCookies) pc->draw();
	for (auto& p : players) p->draw();
	for (auto& e : enemies) e->draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}

void Game::saveScore()
{
	int score = pacman.getComponent<ScoreComponent>().entityScore;
	std::fstream scoreFile(Game::scoreFilePath, std::fstream::out);

	if (score > highScore) {
		scoreFile << score;
	}

	scoreFile.close();
}

void Game::loadHighestScore()
{
	std::fstream scoreFile(Game::scoreFilePath, std::fstream::in);
	scoreFile >> highScore;
	scoreFile.close();
}
