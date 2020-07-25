#pragma once

#include "SDL.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "cleanup.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	~SpriteComponent() {
		cleanup(texture);
	}

	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 60;
		srcRect.h = transform->height;
		srcRect.w = transform->width;
	}

	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, NULL, SDL_FLIP_NONE);
	}
};

