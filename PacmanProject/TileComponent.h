#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileId;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileId = id;

		switch (tileId)
		{
		case 0:
			path = "down_wall.png";
			break;
		case 1:
			path = "up_wall.png";
			break;
		case 2:
			path = "left_wall.png";
			break;
		case 3:
			path = "right_wall.png";
			break;
		case 9:
			path = "cookie.png";
			break;
		default:
			break;
		}
	}

	void init() override {
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};
