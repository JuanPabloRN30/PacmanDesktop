#pragma once

#include "Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyBoardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
				case SDLK_DOWN:
					transform->velocity.x = 0;
					transform->velocity.y = 1;
					sprite->setAngle(180.0);
					break;
				case SDLK_UP:
					transform->velocity.x = 0;
					transform->velocity.y = -1;
					sprite->setAngle(0);
					break;
				case SDLK_LEFT:
					transform->velocity.x = -1;
					transform->velocity.y = 0;
					sprite->setAngle(270.0);
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 1;
					transform->velocity.y = 0;
					sprite->setAngle(90.0);
					break;
				default:
					break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
		}
	}

};

