#include <fstream>
#include <sstream>
#include <time.h>

#include "Components.h"
#include "GameWindow.h"
#include "res_path.h"
#include "Map.h"
#include "Collision.h"


Manager gameManager;
Map* map;

// CHARACTERS
auto& pacman(gameManager.addEntity());
auto& cyanGhost(gameManager.addEntity());
auto& orangeGhost(gameManager.addEntity());
auto& pinkGhost(gameManager.addEntity());
auto& redGhost(gameManager.addEntity());

// UI
auto& label(gameManager.addEntity());
auto& highScoreLabel(gameManager.addEntity());

bool GameWindow::_init()
{
	srand(time(nullptr));

	_isRunning = true;

	TTF_Font* mainFont = Window::_assets->getFont(Constants::GAME_FONT_ID);
	if (mainFont == nullptr) {
		Window::_assets->addFont(Constants::GAME_FONT_ID, Constants::GAME_FONT_FILE);
	}

	SoundEffect* chomp = Window::_assets->getSoundEffect(Constants::CHOMP_ID);
	if (chomp == nullptr) {
		Window::_assets->addSoundEffect(Constants::CHOMP_ID, Constants::CHOMP_FILE);
	}

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
	pacman.addGroup(GameWindow::groupPlayer);

	// GHOST
	int cyanGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int cyanGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	cyanGhost.addComponent<TransformComponent>(cyanGhostInitPosX, cyanGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	cyanGhost.addComponent<GhostSpriteComponent>("cyan_ghost.png", true);
	cyanGhost.addComponent<RandomMovementComponent>();
	cyanGhost.addComponent<ColliderComponent>("enemy");
	cyanGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	cyanGhost.addGroup(GameWindow::groupEnemies);

	int orangeGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int orangeGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	orangeGhost.addComponent<TransformComponent>(orangeGhostInitPosX, orangeGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	orangeGhost.addComponent<GhostSpriteComponent>("orange_ghost.png", true);
	orangeGhost.addComponent<RandomMovementComponent>();
	orangeGhost.addComponent<ColliderComponent>("enemy");
	orangeGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	orangeGhost.addGroup(GameWindow::groupEnemies);

	int pinkGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int pinkGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	pinkGhost.addComponent<TransformComponent>(pinkGhostInitPosX, pinkGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	pinkGhost.addComponent<GhostSpriteComponent>("pink_ghost.png", true);
	pinkGhost.addComponent<RandomMovementComponent>();
	pinkGhost.addComponent<ColliderComponent>("enemy");
	pinkGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	pinkGhost.addGroup(GameWindow::groupEnemies);

	int redGhostInitPosX = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT + 1;
	int redGhostInitPosY = 1 * Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT + 1;
	redGhost.addComponent<TransformComponent>(redGhostInitPosX, redGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	redGhost.addComponent<GhostSpriteComponent>("red_ghost.png", true);
	redGhost.addComponent<RandomMovementComponent>();
	redGhost.addComponent<ColliderComponent>("enemy");
	redGhost.addComponent<ScoreComponent>(Constants::GHOST_SCORE);
	redGhost.addGroup(GameWindow::groupEnemies);

	std::stringstream ss;
	std::stringstream ss1;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.addComponent<UILabel>(Constants::PLAYER_ONE_SCORE_X, Constants::PLAYER_ONE_SCORE_Y, ss.str().c_str(), Constants::GAME_FONT_ID, Constants::WHITE);
	label.addGroup(groupLabels);

	loadHighestScore();
	ss1 << "High score: " << highScore;
	highScoreLabel.addComponent<UILabel>(Constants::HIGH_SCORE_X, Constants::HIGH_SCORE_Y, ss1.str().c_str(), Constants::GAME_FONT_ID, Constants::WHITE);
	highScoreLabel.addGroup(groupLabels);

	return true;
}

void GameWindow::_handleEvents(SDL_Event& event)
{
}

auto& tiles(gameManager.getGroup(GameWindow::groupMap));
auto& players(gameManager.getGroup(GameWindow::groupPlayer));
auto& enemies(gameManager.getGroup(GameWindow::groupEnemies));
auto& colliders(gameManager.getGroup(GameWindow::groupColliders));
auto& cookies(gameManager.getGroup(GameWindow::groupCookies));
auto& powerCookies(gameManager.getGroup(GameWindow::groupPowerCookies));
auto& gameLabels(gameManager.getGroup(GameWindow::groupLabels));

void GameWindow::update()
{
	Vector2D pacmanPos = pacman.getComponent<TransformComponent>().position;
	Vector2D cyanGhostPos = cyanGhost.getComponent<TransformComponent>().position;
	Vector2D orangeGhostPos = orangeGhost.getComponent<TransformComponent>().position;
	Vector2D pinkGhostPos = pinkGhost.getComponent<TransformComponent>().position;
	Vector2D redGhostPos = redGhost.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "1UP " << pacman.getComponent<ScoreComponent>().entityScore;
	label.getComponent<UILabel>().setLabelText(ss.str().c_str());

	gameManager.refresh();
	gameManager.update();

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
		_isRunning = false;
		saveScore();
	}

}

void GameWindow::render()
{
	SDL_RenderClear(_renderer);

	SDL_RenderSetViewport(_renderer, &Constants::TOP_VIEWPORT);
	for (auto& l : gameLabels) l->draw();

	SDL_RenderSetViewport(_renderer, &Constants::BOTTOM_VIEWPORT);
	for (auto& t : tiles) t->draw();
	//for (auto& c : colliders) c->draw();
	for (auto& c : cookies) c->draw();
	for (auto& pc : powerCookies) pc->draw();
	for (auto& p : players) p->draw();
	for (auto& e : enemies) e->draw();
	SDL_RenderPresent(_renderer);
}

void GameWindow::_clean() {

}

void GameWindow::saveScore()
{
	int score = pacman.getComponent<ScoreComponent>().entityScore;
	std::fstream scoreFile(Constants::HIGH_SCORE_FILE, std::fstream::out);

	if (score > highScore) {
		scoreFile << score;
	}

	scoreFile.close();
}

void GameWindow::loadHighestScore()
{
	std::fstream scoreFile(Constants::HIGH_SCORE_FILE, std::fstream::in);
	scoreFile >> highScore;
	scoreFile.close();
}