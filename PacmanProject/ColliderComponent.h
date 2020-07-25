#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "TransformComponent.h"

class ColliderComponent : public  Component
{
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		collider.x = transform->position.x;
		collider.y = transform->position.y;
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};

