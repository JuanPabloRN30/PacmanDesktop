#pragma once

#include <stdlib.h>
#include "ECS.h"
#include "TransformComponent.h"

class RandomMovementComponent : public Component
{
private:
	TransformComponent* transform;
public:
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		int randVal = rand() % 4;
		switch (randVal) {
			case 0:
				transform->velocity.x = 0;
				transform->velocity.y = 1;
				break;
			case 1:
				transform->velocity.x = 0;
				transform->velocity.y = -1;
				break;
			case 2:
				transform->velocity.x = -1;
				transform->velocity.y = 0;
				break;
			case 3:
				transform->velocity.x = 1;
				transform->velocity.y = 0;
				break;
		}
	}
};
