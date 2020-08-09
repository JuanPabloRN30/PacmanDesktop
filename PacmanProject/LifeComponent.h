#pragma once

#include "Constants.h"
#include "SDL.h"
#include "ECS.h"
#include <algorithm>
#include "TextureManager.h"
#include "TransformComponent.h"
#include "Constants.h"

class LifeComponent : public Component
{
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int lifes = Constants::DEFAULT_N_LIFES;

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

		srcRect = { 0, 1 * transform->height + Constants::PIXEL_SEPARATION, transform->width, transform->height};
	}

	void draw() override {
		for (int i = 0; i < lifes; i++) {
			destRect = { i * transform->width, Constants::SCREEN_HEIGHT - transform->height, transform->width, transform->height};
			TextureManager::Draw(texture, srcRect, destRect, Constants::LEFT_ANGLE, SDL_FLIP_NONE);
		}
	}

	void loseLife() {
		lifes = std::max(0, lifes - 1);
	}

	bool isAlive() {
		return lifes > 0;
	}
};

