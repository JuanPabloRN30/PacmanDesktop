#pragma once

#include <stdlib.h>
#include "ECS.h"
#include "TransformComponent.h"
#include "Constants.h"

class RandomMovementComponent : public Component
{
private:
	TransformComponent* transform;
	Vector2D source, dest;
public:
	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		source = transform->position;
		updateDestinationPoint();
	}

	void update() override {
		source = transform->position;

		if (source.x == dest.x && source.y == dest.y) {
			updateDestinationPoint();
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

	void updateDestinationPoint() {
		dest.x = rand() % (Constants::MAP_SIZE_X * Constants::MAP_TILE_SIZE * Constants::MAP_SCALE);
		dest.y = rand() % (Constants::MAP_SIZE_Y * Constants::MAP_TILE_SIZE * Constants::MAP_SCALE);

	}
};
