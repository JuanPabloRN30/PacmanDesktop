#pragma once

#include "SDL.h"
#include "PositionComponent.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	PositionComponent *position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 60;
		destRect.w = destRect.h = 60;
	}

	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, NULL, SDL_FLIP_NONE);
	}
};

