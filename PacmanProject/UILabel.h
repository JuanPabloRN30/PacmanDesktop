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
	UILabel(int xpos, int ypos, const char* text, const char* font, SDL_Color &colour)  :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		setLabelText(text);
	}

	~UILabel() {}

	void setLabelText(const char* lt) {
		labelText = lt;
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(labelFont), labelText, textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		cleanup(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}
private:
	SDL_Rect position;
	const char* labelText;
	const char* labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
