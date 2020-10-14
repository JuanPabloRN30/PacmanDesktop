#pragma once

#include "SpriteComponent.h"
#include "cleanup.h"
#include <algorithm>
#include "Constants.h"

class GhostAnimationTag : public AnimationTag {
public:
	static const int scared_blue = 2;
	static const int scared_white = 3;
};

class GhostSpriteComponent : public SpriteComponent
{
public:
	int scaredDuration = 10000;
	int scaredBeginSeconds;
	int scaredBeginAnimationSeconds = 2000;
	int scaredAnimationChange = 1000;

	GhostSpriteComponent(const char* path, bool isAnimated) {
		setTexture(path);
		animated = isAnimated;

		Animation move = Animation(0, 0, 2, 200);
		Animation scared_blue = Animation(4, 0, 2, 200);
		Animation scared_white = Animation(5, 0, 2, 200);

		animations.emplace(GhostAnimationTag::move, move);
		animations.emplace(GhostAnimationTag::scared_blue, scared_blue);
		animations.emplace(GhostAnimationTag::scared_white, scared_white);
	}

	~GhostSpriteComponent(){
		cleanup(texture);
	}

	void update() override {
		auto updateBeginMiliSec = SDL_GetTicks();
		if (animationTag == GhostAnimationTag::scared_blue || animationTag == GhostAnimationTag::scared_white) { // scared
			if (static_cast<int>(updateBeginMiliSec - scaredBeginSeconds) >= scaredBeginAnimationSeconds) {
				int move = static_cast<int>(updateBeginMiliSec / scaredAnimationChange) % 2;
				if(move == 0)
					setAnimation(GhostAnimationTag::scared_blue);
				if(move == 1)
					setAnimation(GhostAnimationTag::scared_white);
			}
			if (static_cast<int>(updateBeginMiliSec - scaredBeginSeconds) >= scaredDuration) {
				setAnimation(GhostAnimationTag::move);
			}
		}

		if (animationTag == GhostAnimationTag::move) {
			if (transform->getDirection() == TransformComponent::direction::left) animIndexX = 0;
			if (transform->getDirection() == TransformComponent::direction::up) animIndexX = 1;
			if (transform->getDirection() == TransformComponent::direction::right) animIndexX = 2;
			if (transform->getDirection() == TransformComponent::direction::down) animIndexX = 3;
		}

		if (animated) {
			int srcY = static_cast<int>((updateBeginMiliSec / speed) % frames);
			srcRect.y = srcRect.h * srcY + (Constants::PIXEL_SEPARATION * srcY);
		}

		srcRect.x = animIndexX * transform->width + (Constants::PIXEL_SEPARATION * animIndexX);

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, angle, spriteFlip);
	}

	void setAnimation(int tag) {
		if (animationTag == GhostAnimationTag::move && tag == GhostAnimationTag::scared_blue) scaredBeginSeconds = SDL_GetTicks();
		animationTag = tag;
		animIndexX = animations[animationTag].indexX;
		frames = animations[animationTag].frames;
		speed = animations[animationTag].speed;

		/*srcRect.x = animations[animationTag].indexX;
		srcRect.y = animations[animationTag].indexY;*/
	}
};
