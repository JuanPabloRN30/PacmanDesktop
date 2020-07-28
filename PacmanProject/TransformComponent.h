#pragma once

#include "ECS.h"
#include "Vector2D.h"

class TransformComponent : public Component
{

public:

	enum direction : std::size_t {
		down,
		up,
		left,
		right
	};

	Vector2D position;
	Vector2D velocity;

	int height = 60;
	int width = 60;
	int scale = 1;

	int speed = 1;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(double x, double y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(double x, double y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	direction getDirection() {
		if (velocity.x < 0) return left;
		if (velocity.y < 0) return up;
		if (velocity.x > 0) return right;
		if (velocity.y > 0) return down;
	}
};
