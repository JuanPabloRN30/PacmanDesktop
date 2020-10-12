#include "SDL_ttf.h"

#include "Constants.h"
#include "MenuWindow.h"
#include "SoundEffect.h"
#include "Components.h"
#include "GameWindow.h"

SDL_Event MenuWindow::_menuEvent;

Manager manager;
auto& titleLabel(manager.addEntity());
auto& startLabel(manager.addEntity());
auto& quitLabel(manager.addEntity());

void MenuWindow::_clean()
{
}


bool MenuWindow::_init()
{

	TTF_Font* mainFont = Window::_assets->getFont(Constants::MENU_FONT_ID);
	if (mainFont == nullptr) {
		Window::_assets->addFont(Constants::MENU_FONT_ID, Constants::MENU_FONT_FILE, Constants::MENU_FONT_SIZE);
	}
	
	SoundEffect* beginning = Window::_assets->getSoundEffect(Constants::BEGINNING_ID);
	if (beginning == nullptr) {
		Window::_assets->addSoundEffect(Constants::BEGINNING_ID, Constants::BEGINNING_FILE);
	}

	int titleLabelX = Constants::SCREEN_WIDTH / 2;
	int titleLabelY = 0;
	const char* titleText = "TITLE";
	titleLabel.addComponent<UILabel>(titleLabelX, titleLabelY, titleText, Constants::MENU_FONT_ID, Constants::WHITE, true);
	titleLabel.addGroup(MenuWindow::groupTitles);

	int startLabelX = Constants::SCREEN_WIDTH / 2;
	int startLabelY = 0;
	const char* startText = "START";
	startLabel.addComponent<UILabel>(startLabelX, startLabelY, startText, Constants::MENU_FONT_ID, Constants::WHITE, true);
	startLabel.addComponent<ClickComponent>(optionViewport);
	startLabel.addGroup(MenuWindow::groupOptions);
	

	int quitLabelX = Constants::SCREEN_WIDTH / 2;
	int quitLabelY = 50;
	const char* quitText = "QUIT";
	quitLabel.addComponent<UILabel>(quitLabelX, quitLabelY, quitText, Constants::MENU_FONT_ID, Constants::WHITE, true);
	quitLabel.addComponent<ClickComponent>(optionViewport);
	quitLabel.addGroup(MenuWindow::groupOptions);

	_isRunning = true;

	return true;
}

void MenuWindow::_handleEvents(SDL_Event& event)
{
}

bool start = false;

void MenuWindow::update()
{
	manager.refresh();
	manager.update();

	if (startLabel.getComponent<ClickComponent>().isClicked()) {
		
		if (!start) { // TODO: CHECK
			GameWindow* gameWindow = new GameWindow();
			Game::currentWindow = gameWindow;
			gameWindow->init();
			start = true;
			SDL_DestroyWindow(_window);
		}
	}

	if (quitLabel.getComponent<ClickComponent>().isClicked()) {
		_isRunning = false;
	}
}

auto& titles = manager.getGroup(MenuWindow::groupTitles);
auto& options = manager.getGroup(MenuWindow::groupOptions);
auto& footers = manager.getGroup(MenuWindow::groupFooters);

void MenuWindow::render()
{
	SDL_RenderClear(_renderer);

	SDL_RenderSetViewport(_renderer, &titleViewport);
	for (auto& t : titles) t->draw();

	SDL_RenderSetViewport(_renderer, &optionViewport);
	for (auto& o : options) o->draw();

	SDL_RenderSetViewport(_renderer, &footerViewport);
	for (auto& f : footers) f->draw();

	SDL_RenderPresent(_renderer);
}
