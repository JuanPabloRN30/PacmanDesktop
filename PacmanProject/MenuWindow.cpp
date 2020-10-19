#include "SDL_ttf.h"

#include "Constants.h"
#include "MenuWindow.h"
#include "SoundEffect.h"
#include "Components.h"
#include "GameWindow.h"


constexpr int INF = 1000000000;
SDL_Event MenuWindow::_menuEvent;

Manager manager;
auto& titleLabel(manager.addEntity());
auto& startLabel(manager.addEntity());
auto& quitLabel(manager.addEntity());
auto& menuPacman(manager.addEntity());
auto& menuRedGhost(manager.addEntity());
auto& menuPinkGhost(manager.addEntity());
auto& menuCyanGhost(manager.addEntity());
auto& menuOrangeGhost(manager.addEntity());

void MenuWindow::_clean()
{
}


bool MenuWindow::_init()
{

	TTF_Font* mainFont = Window::_assets->getFont(Constants::MENU_FONT_ID);
	if (mainFont == nullptr) {
		Window::_assets->addFont(Constants::MENU_FONT_ID, Constants::MENU_FONT_FILE, Constants::MENU_FONT_SIZE);
	}

	TTF_Font* menuTitleFont = Window::_assets->getFont(Constants::MENU_TITLE_FONT_ID);
	if (mainFont == nullptr) {
		Window::_assets->addFont(Constants::MENU_TITLE_FONT_ID, Constants::MENU_TITLE_FONT_FILE, Constants::MENU_TITLE_FONT_SIZE);
	}
	
	SoundEffect* beginning = Window::_assets->getSoundEffect(Constants::INTERMISSION_ID);
	if (beginning == nullptr) {
		Window::_assets->addSoundEffect(Constants::INTERMISSION_ID, Constants::INTERMISSION_FILE);
	}

	int titleLabelX = Constants::SCREEN_WIDTH / 2;
	int titleLabelY = titleViewport.h / 2;
	const char* titleText = "PACMAN";
	titleLabel.addComponent<UILabel>(titleLabelX, titleLabelY, titleText, Constants::MENU_TITLE_FONT_ID, Constants::YELLOW, true);
	titleLabel.addGroup(MenuWindow::groupTitles);

	int startLabelX = Constants::SCREEN_WIDTH / 2;
	int startLabelY = static_cast<int>(optionViewport.h * .3);
	const char* startText = "START";
	startLabel.addComponent<UILabel>(startLabelX, startLabelY, startText, Constants::MENU_FONT_ID, Constants::WHITE, true);
	startLabel.addComponent<ClickComponent>(optionViewport);
	startLabel.addGroup(MenuWindow::groupOptions);
	

	int quitLabelX = Constants::SCREEN_WIDTH / 2;
	int quitLabelY = static_cast<int>(optionViewport.h * .3) + 70;
	const char* quitText = "QUIT";
	quitLabel.addComponent<UILabel>(quitLabelX, quitLabelY, quitText, Constants::MENU_FONT_ID, Constants::WHITE, true);
	quitLabel.addComponent<ClickComponent>(optionViewport);
	quitLabel.addGroup(MenuWindow::groupOptions);

	// PACMAN
	int pacman_init_pos_x = Constants::SCREEN_WIDTH + Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT;
	int pacman_init_pos_y = Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT;
	menuPacman.addComponent<TransformComponent>(pacman_init_pos_x, pacman_init_pos_y, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	menuPacman.addComponent<SpriteComponent>("pacman.png", true);
	menuPacman.addGroup(MenuWindow::groupPlayers);

	int distanceFromPacman = 100;

	// GHOST
	int cyanGhostInitPosX = Constants::SCREEN_WIDTH + Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT * 2 + distanceFromPacman;
	int cyanGhostInitPosY = Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT;
	menuCyanGhost.addComponent<TransformComponent>(cyanGhostInitPosX, cyanGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	menuCyanGhost.addComponent<GhostSpriteComponent>("cyan_ghost.png", true);
	menuCyanGhost.getComponent<GhostSpriteComponent>().scaredBeginAnimationSeconds = INF;
	menuCyanGhost.addGroup(MenuWindow::groupEnemies);

	int orangeGhostInitPosX = Constants::SCREEN_WIDTH +  Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT * 3 + 5 + distanceFromPacman;
	int orangeGhostInitPosY = Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT;
	menuOrangeGhost.addComponent<TransformComponent>(orangeGhostInitPosX, orangeGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	menuOrangeGhost.addComponent<GhostSpriteComponent>("orange_ghost.png", true);
	menuOrangeGhost.getComponent<GhostSpriteComponent>().scaredBeginAnimationSeconds = INF;
	menuOrangeGhost.addGroup(MenuWindow::groupEnemies);

	int pinkGhostInitPosX = Constants::SCREEN_WIDTH +  Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT * 4 + 10 + distanceFromPacman;
	int pinkGhostInitPosY = Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT;
	menuPinkGhost.addComponent<TransformComponent>(pinkGhostInitPosX, pinkGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	menuPinkGhost.addComponent<GhostSpriteComponent>("pink_ghost.png", true);
	menuPinkGhost.getComponent<GhostSpriteComponent>().scaredBeginAnimationSeconds = INF;
	menuPinkGhost.addGroup(MenuWindow::groupEnemies);

	int redGhostInitPosX = Constants::SCREEN_WIDTH + Constants::ENTITY_SCALE * Constants::ENTITY_WIDHT * 5 + 15 + distanceFromPacman;
	int redGhostInitPosY = Constants::ENTITY_SCALE * Constants::ENTITY_HEIGHT;
	menuRedGhost.addComponent<TransformComponent>(redGhostInitPosX, redGhostInitPosY, Constants::ENTITY_HEIGHT, Constants::ENTITY_WIDHT, Constants::ENTITY_SCALE);
	menuRedGhost.addComponent<GhostSpriteComponent>("red_ghost.png", true);
	menuRedGhost.getComponent<GhostSpriteComponent>().scaredBeginAnimationSeconds = INF;
	menuRedGhost.addGroup(MenuWindow::groupEnemies);

	_isRunning = true;

	_assets->getSoundEffect(Constants::INTERMISSION_ID)->play(-1);

	return true;
}

void MenuWindow::_handleEvents(SDL_Event& event)
{
}

bool left = true;
auto& titles = manager.getGroup(MenuWindow::groupTitles);
auto& options = manager.getGroup(MenuWindow::groupOptions);
auto& menuPlayers = manager.getGroup(MenuWindow::groupPlayers);
auto& menuEnemies = manager.getGroup(MenuWindow::groupEnemies);

void MenuWindow::update()
{
	manager.refresh();
	manager.update();

	if (startLabel.getComponent<ClickComponent>().isClicked()) {
		
		if (!buttonPressed) {
			GameWindow* gameWindow = new GameWindow();
			Game::currentWindow = gameWindow;
			if (!gameWindow->init()) return;
			buttonPressed = true;
			SDL_DestroyWindow(_window);
			clean();
		}
	}

	if (quitLabel.getComponent<ClickComponent>().isClicked()) {
		if (!buttonPressed){
			_isRunning = false;
			buttonPressed = true;
		}
	}

	bool isOutsideLeft = true;
	bool isOutsideRight = true;
	for (auto& p : menuPlayers) {
		auto& transformComponent = p->getComponent<TransformComponent>();
		if (transformComponent.position.x < Constants::SCREEN_WIDTH) isOutsideRight = false;
		if (transformComponent.position.x + transformComponent.width >= 0) isOutsideLeft = false;
	}
	for (auto& e : menuEnemies) {
		auto& transformComponent = e->getComponent<TransformComponent>();
		if (transformComponent.position.x < Constants::SCREEN_WIDTH) isOutsideRight = false;
		if (transformComponent.position.x + transformComponent.width >= 0) isOutsideLeft = false;
	}

	if (!isOutsideLeft && isOutsideRight)
		left = false;

	if (isOutsideLeft && !isOutsideRight)
		left = true;

	int xVelocity = 3;
	int yVelocity = 0;
	if (left) {
		menuPacman.getComponent<SpriteComponent>().setAngle(90);
		for (auto& p : menuPlayers) {
			p->getComponent<TransformComponent>().velocity.x = xVelocity;
			p->getComponent<TransformComponent>().velocity.y = yVelocity;
		}
		for (auto& e : menuEnemies) {
			e->getComponent<TransformComponent>().velocity.x = xVelocity;
			e->getComponent<TransformComponent>().velocity.y = yVelocity;
			if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::move)
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::scared_blue);
		}
	}
	else {
		menuPacman.getComponent<SpriteComponent>().setAngle(270);
		for (auto& p : menuPlayers) {
			p->getComponent<TransformComponent>().velocity.x = -xVelocity;
			p->getComponent<TransformComponent>().velocity.y = yVelocity;
		}
		for (auto& e : menuEnemies) {
			e->getComponent<TransformComponent>().velocity.x = -xVelocity;
			e->getComponent<TransformComponent>().velocity.y = yVelocity;
			if (e->getComponent<GhostSpriteComponent>().animationTag == GhostAnimationTag::scared_blue)
				e->getComponent<GhostSpriteComponent>().setAnimation(GhostAnimationTag::move);
		}
	}
}

void MenuWindow::render()
{
	SDL_RenderClear(_renderer);

	SDL_RenderSetViewport(_renderer, &titleViewport);
	for (auto& t : titles) t->draw();

	SDL_RenderSetViewport(_renderer, &optionViewport);
	for (auto& o : options) o->draw();

	SDL_RenderSetViewport(_renderer, &footerViewport);
	for (auto& p : menuPlayers) p->draw();
	for (auto& e : menuEnemies) e->draw();

	SDL_RenderPresent(_renderer);
}
