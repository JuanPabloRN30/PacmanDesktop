#pragma once

#include "SDL.h"
#include "ECS.h"
#include <algorithm>
#include "TextureManager.h"
#include "TransformComponent.h"

class LifeComponent : public Component
{
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int lifes = 3;

	LifeComponent() = default;

	LifeComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	LifeComponent(int l, const char* path) {
		lifes = l;
		texture = TextureManager::LoadTexture(path);
	}

	~LifeComponent() {}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect = { 0, 1 * transform->height + 1, transform->width, transform->height};
	}

	void draw() override {
		for (int i = 0; i < lifes; i++) {
			destRect = { i * transform->width, Game::SCREEN_HEIGHT - transform->height, transform->width, transform->height};
			TextureManager::Draw(texture, srcRect, destRect, 270, SDL_FLIP_NONE);
		}
	}

	void loseLife() {
		lifes = std::max(0, lifes - 1);
	}

	bool isAlive() {
		return lifes > 0;
	}
};

