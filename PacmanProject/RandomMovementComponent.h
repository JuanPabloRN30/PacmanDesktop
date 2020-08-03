#pragma once

#include <stdlib.h>
#include "ECS.h"
#include "TransformComponent.h"

class RandomMovementComponent : public Component
{
private:
	TransformComponent* transform;
	Vector2D source, dest;
public:
	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		source = transform->position;
		dest.x = rand() % Game::SCREEN_WIDTH;
		dest.y = rand() % Game::SCREEN_HEIGHT;
	}

	void update() override {
		source = transform->position;

		if (source.x == dest.x && source.y == dest.y) {
			dest.x = rand() % Game::SCREEN_WIDTH;
			dest.y = rand() % Game::SCREEN_HEIGHT;
		}

		if (source.x < dest.x) {
			transform->velocity.x = 1;
			transform->velocity.y = 0;
			return;
		}

		if (source.x > dest.x) {
			transform->velocity.x = -1;
			transform->velocity.y = 0;
			return;
		}

		if (source.y < dest.y) {
			transform->velocity.x = 0;
			transform->velocity.y = 1;
			return;
		}

		if (source.y > dest.y) {
			transform->velocity.x = 0;
			transform->velocity.y = -1;
			return;
		}

	}
};
