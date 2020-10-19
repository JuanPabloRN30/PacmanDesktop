#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "cleanup.h"

#include "SDL.h"
#include "SDL_ttf.h"

class UILabel : public Component
{
public:
	SDL_Rect position;

	UILabel(int xpos, int ypos, const char* text, const char* font, SDL_Color &colour, bool centered = false)  :
		labelText(text), labelFont(font), textColour(colour), centered(centered)
	{
		position.x = xpos;
		position.y = ypos;

		setLabelText(text);
	}

	~UILabel() {}

	void setLabelText(const char* lt) {
		labelText = lt;
		
		SDL_Surface* surf = TTF_RenderText_Blended(Game::currentWindow->_assets->getFont(labelFont), labelText, textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::currentWindow->_renderer, surf);
		cleanup(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

		if (centered) {
			position.x = Constants::SCREEN_WIDTH / 2 - position.w / 2;
		}
	}

	void draw() override {
		SDL_RenderCopy(Game::currentWindow->_renderer, labelTexture, nullptr, &position);
	}
private:
	bool centered;
	const char* labelText;
	const char* labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
