#include "Game.h"

#include<iostream>
#include <time.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "res_path.h"
#include "cleanup.h"
#include "AssetManager.h"
#include <sstream>
#include <fstream>
#include "Constants.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Mix_Chunk* Game::pacmanChomp = nullptr;
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		TextureManager::LogSDLError(std::cout, "SDL_Mixer error");
		return false;
	}

	isRunning = true;

	window = SDL_CreateWindow("Pacman game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateWindow");
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		TextureManager::LogSDLError(std::cout, "CreateRenderer");
		return false;
	}

	assets->addFont("arial", "arial.ttf", Constants::FONT_SIZE);

	const std::string resPath = getResourcePath("PacmanProject");
	const std::string pacmanFile = resPath + "pacman.png";

	map = new Map("pacmanboardv5.png", Constants::MAP_SCALE, Constants::MAP_TILE_SIZE);
	map->loadMap("map.map", Constants::MAP_SIZE_X, Constants::MAP_SIZE_Y);

	// PACMAN
	int pacman_init_pos_x = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int pacman_init_pos_y = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	pacman.addComponent<TransformComponent>(pacman_init_pos_x, pacman_init_pos_y, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	pacman.addComponent<SpriteComponent>(pacmanFile.c_str(), true);
	pacman.addComponent<KeyBoardController>();
	pacman.addComponent<ColliderComponent>("player");
	pacman.addComponent<ScoreComponent>();
	pacman.addComponent<LifeComponent>(pacmanFile.c_str());
	pacman.addGroup(groupPlayer);

	// GHOST
	int cyanGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int cyanGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	cyanGhost.addComponent<TransformComponent>(cyanGhostInitPosX, cyanGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	cyanGhost.addComponent<GhostSpriteComponent>("cyan_ghost.png", true);
	cyanGhost.addComponent<RandomMovementComponent>();
	cyanGhost.addComponent<ColliderComponent>("enemy");
	cyanGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	cyanGhost.addGroup(groupEnemies);
	
	int orangeGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int orangeGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	orangeGhost.addComponent<TransformComponent>(orangeGhostInitPosX, orangeGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	orangeGhost.addComponent<GhostSpriteComponent>("orange_ghost.png", true);
	orangeGhost.addComponent<RandomMovementComponent>();
	orangeGhost.addComponent<ColliderComponent>("enemy");
	orangeGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	orangeGhost.addGroup(groupEnemies);
	
	int pinkGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int pinkGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	pinkGhost.addComponent<TransformComponent>(pinkGhostInitPosX, pinkGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	pinkGhost.addComponent<GhostSpriteComponent>("pink_ghost.png", true);
	pinkGhost.addComponent<RandomMovementComponent>();
	pinkGhost.addComponent<ColliderComponent>("enemy");
	pinkGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	pinkGhost.addGroup(groupEnemies);

	int redGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int redGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	redGhost.addComponent<TransformComponent>(redGhostInitPosX, redGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	redGhost.addComponent<GhostSpriteComponent>("red_ghost.png", true);
	redGhost.addComponent<RandomMovementComponent>();
	redGhost.addComponent<ColliderComponent>("enemy");
	redGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	redGhost.addGroup(groupEnemies);

	std::stringstream ss;
	std::stringstream ss1;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.addComponent<UILabel>(Constants::PLAYER_ONE_SCORE_X, Constants::PLAYER_ONE_SCORE_Y, ss.str().c_str(), "arial", Constants::WHITE);
	label.addGroup(groupLabels);

	loadHighestScore();
	ss1 << "High score: " << highScore;
	highScoreLabel.addComponent<UILabel>(Constants::HIGH_SCORE_X, Constants::HIGH_SCORE_Y, ss1.str().c_str(), "arial", Constants::WHITE);
	highScoreLabel.addGroup(groupLabels);

	pacmanChomp = Mix_LoadWAV("pacman_chomp.wav");
	if (pacmanChomp == nullptr)
	{
		TextureManager::LogSDLError(std::cout, "Chomp music error");
		return false;
	}
	Mix_PlayChannel(-1, pacmanChomp, 0);


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
	Vector2D cyanGhostPos = cyanGhost.getComponent<TransformComponent>().position;
	Vector2D orangeGhostPos = orangeGhost.getComponent<TransformComponent>().position;
	Vector2D pinkGhostPos = pinkGhost.getComponent<TransformComponent>().position;
	Vector2D redGhostPos = redGhost.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.getComponent<UILabel>().setLabelText(ss.str().c_str());

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			pacman.getComponent<TransformComponent>().position = pacmanPos;
		}
		if (Collision::AABB(cyanGhost.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			cyanGhost.getComponent<TransformComponent>().position = cyanGhostPos;
			cyanGhost.getComponent<RandomMovementComponent>().updateDestinationPoint();
		}
		if (Collision::AABB(orangeGhost.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			orangeGhost.getComponent<TransformComponent>().position = orangeGhostPos;
			orangeGhost.getComponent<RandomMovementComponent>().updateDestinationPoint();
		}
		if (Collision::AABB(pinkGhost.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			pinkGhost.getComponent<TransformComponent>().position = pinkGhostPos;
			pinkGhost.getComponent<RandomMovementComponent>().updateDestinationPoint();
		}
		if (Collision::AABB(redGhost.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
			redGhost.getComponent<TransformComponent>().position = redGhostPos;
			redGhost.getComponent<RandomMovementComponent>().updateDestinationPoint();
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
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::scared_blue);
			}
			pc->destroy();
		}
	}

	for (auto& e : enemies) {
		// check collision with enemies
		if (Collision::AABB(pacman.getComponent<ColliderComponent>(), e->getComponent<ColliderComponent>())) {
			if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::scared_blue || e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::scared_white) {
				e->getComponent<TransformComponent>().reset();
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::move);
				pacman.getComponent<ScoreComponent>().addEntityScore(e->getComponent<ScoreComponent>().score);
				for (auto& e : enemies) {
					e->getComponent<ScoreComponent>().setScore(e->getComponent<ScoreComponent>().score * Constants::GHOST_MULTIPLIER);
				}
			}
			else {
				/*pacman.getComponent<LifeComponent>().loseLife();
				pacman.getComponent<TransformComponent>().reset();
				for (auto& e : enemies) {
					e->getComponent<TransformComponent>().reset();
				}*/
			}
		}

		if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::move) {
			e->getComponent<ScoreComponent>().setScore(Constants::GHOST_SCORE);
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

	SDL_RenderSetViewport(renderer, &Constants::TOP_VIEWPORT);
	for (auto& l : labels) l->draw();

	SDL_RenderSetViewport(renderer, &Constants::BOTTOM_VIEWPORT);
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
	Mix_FreeChunk(Game::pacmanChomp);
	Mix_Quit();
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
