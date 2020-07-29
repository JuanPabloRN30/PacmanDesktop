#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "Game.h"
#include "TextureManager.h"
#include "cleanup.h"

class ColliderComponent : public  Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	~ColliderComponent() {
		cleanup(tex);
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("collider.png");
		srcRect = { 0, 0, 60, 60 };
		destRect = { collider.x, collider.y, collider.w, collider.h};
	}

	void update() override {

		if (tag != "map") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destRect.x = collider.x;
		destRect.y = collider.y;
	}

	void draw() override {
		TextureManager::Draw(tex, srcRect, destRect, NULL, SDL_FLIP_NONE);
	}
};
