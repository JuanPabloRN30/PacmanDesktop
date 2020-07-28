#pragma once

#include "SpriteComponent.h"

class GhostSpriteComponent : public SpriteComponent
{
public:
	GhostSpriteComponent(const char* path, bool isAnimated) {
		setTexture(path);
		animated = isAnimated;

		Animation move = Animation(0, 2, 100);
		Animation scared = Animation(4, 2, 1000);
		animations.emplace("Move", move);
		animations.emplace("Scared", scared);
	}

	void update() override {
		int srcY = static_cast<int>((SDL_GetTicks() / speed) % frames);

		if (animated) {
			srcRect.y = srcRect.h * srcY + (5 * srcY);
		}

		if (animIndex != 4) {
			if (transform->getDirection() == TransformComponent::left) animIndex = 0;
			if (transform->getDirection() == TransformComponent::up) animIndex = 1;
			if (transform->getDirection() == TransformComponent::right) animIndex = 2;
			if (transform->getDirection() == TransformComponent::down) animIndex = 3;
		}
		srcRect.x = animIndex * transform->width + (5 * animIndex);

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
};
