#pragma once

#include "ECS.h"
#include "Vector2D.h"
#include "Constants.h"

class TransformComponent : public Component
{

public:

	enum class direction : std::size_t {
		down,
		up,
		left,
		right
	};

	Vector2D initialPosition;
	Vector2D position;
	Vector2D velocity;

	int height = Constants::ENTITY_HEIGHT;
	int width = Constants::ENTITY_WIDHT;
	int scale = Constants::ENTITY_SCALE;

	int speed = Constants::ENTITY_SPEED;

	TransformComponent() {
		position.Zero();

		initialPosition = position;
	}

	TransformComponent(double x, double y) {
		position.x = x;
		position.y = y;

		initialPosition = position;
	}

	TransformComponent(double x, double y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;

		initialPosition = position;
	}

	void reset() {
		position = initialPosition;
		init();
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	direction getDirection() {
		if (velocity.x < 0) return direction::left;
		if (velocity.y < 0) return direction::up;
		if (velocity.x > 0) return direction::right;
		if (velocity.y > 0) return direction::down;
		return direction::left;
	}
};
