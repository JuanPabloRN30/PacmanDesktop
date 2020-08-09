#pragma once

#include "SDL.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "cleanup.h"
#include "Animation.h"
#include "Constants.h"
#include <map>

class AnimationTag {
public:
	static const int move = 0;
};

class SpriteComponent : public Component
{
protected:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	TransformComponent* transform;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	double angle = 0;

public:

	int animationTag;
	int animIndexX = 0;
	int animIndexY = 0;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	std::map<int, Animation> animations;

	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated) {
		setTexture(path);
		animated = isAnimated;

		Animation move = Animation(0, 0, 3, 100);
		animations.emplace(AnimationTag::move, move);
	}

	~SpriteComponent() {
		cleanup(texture);
	}

	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width;
		
		setAnimation(AnimationTag::move);
	}

	void update() override {
		int srcY = static_cast<int>((SDL_GetTicks() / speed) % frames);

		if (animated) {
			srcRect.y = srcRect.h * srcY + (Constants::PIXEL_SEPARATION * srcY);
		}

		srcRect.x = animIndexX * transform->width;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, angle, spriteFlip);
	}

	void setAngle(double a) {
		angle = a;
	}

	void setAnimation(int tag) {
		animationTag = tag;
		animIndexX = animations[animationTag].indexX;
		frames = animations[animationTag].frames;
		speed = animations[animationTag].speed;

		srcRect.x = animations[animationTag].indexX;
		srcRect.y = animations[animationTag].indexY;
	}
};
