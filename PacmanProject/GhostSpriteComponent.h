#pragma once

#include "SpriteComponent.h"
#include "cleanup.h"
#include <algorithm>

class GhostAnimationTag : public AnimationTag {
public:
	static const int scared = 2;
};

class GhostSpriteComponent : public SpriteComponent
{
public:
	int scaredDuration = 10000;
	int scaredBeginSeconds;
	int scaredBeginAnimationSeconds = 2000;

	GhostSpriteComponent(const char* path, bool isAnimated) {
		setTexture(path);
		animated = isAnimated;

		Animation move = Animation(0, 2, 100);
		Animation scared = Animation(4, 2, 300);

		animations.emplace(GhostAnimationTag::move, move);
		animations.emplace(GhostAnimationTag::scared, scared);
	}

	~GhostSpriteComponent(){
		cleanup(texture);
	}

	void update() override {
		auto updateBeginMiliSec = SDL_GetTicks();
		if (animationTag == GhostAnimationTag::scared) { // scared
			animated = false;
			if (static_cast<int>(updateBeginMiliSec - scaredBeginSeconds) >= scaredBeginAnimationSeconds) {
				animated = true;
			}
			if (static_cast<int>(updateBeginMiliSec - scaredBeginSeconds) >= scaredDuration) {
				setAnimation(GhostAnimationTag::move);
			}
		}

		if (animationTag == GhostAnimationTag::move) {
			if (transform->getDirection() == TransformComponent::direction::left) animIndex = 0;
			if (transform->getDirection() == TransformComponent::direction::up) animIndex = 1;
			if (transform->getDirection() == TransformComponent::direction::right) animIndex = 2;
			if (transform->getDirection() == TransformComponent::direction::down) animIndex = 3;
		}

		if (animated) {
			int srcY = static_cast<int>((updateBeginMiliSec / speed) % frames);
			srcRect.y = srcRect.h * srcY + (5 * srcY);
			if (animationTag == GhostAnimationTag::scared) {
				std::cout << animated << " " << srcRect.x << " " << srcRect.y << std::endl;
			}
		}

		srcRect.x = animIndex * transform->width + (5 * animIndex);

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void setAnimation(int tag) {
		animationTag = tag;
		if (animationTag == GhostAnimationTag::scared) scaredBeginSeconds = SDL_GetTicks();
		animIndex = animations[animationTag].index;
		frames = animations[animationTag].frames;
		speed = animations[animationTag].speed;
	}
};
