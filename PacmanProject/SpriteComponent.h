#pragma once

#include "SDL.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "cleanup.h"
#include "Animation.h"
#include <map>

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
	const char* animName;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated) {
		setTexture(path);
		animated = isAnimated;

		Animation move = Animation(0, 3, 100);
		animations.emplace("Move", move);
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
		
		setAnimation("Move");
	}

	void update() override {
		int srcY = static_cast<int>((SDL_GetTicks() / speed) % frames);

		if (animated) {
			srcRect.y = srcRect.h * srcY + (5 * srcY);
		}

		srcRect.x = animIndex * transform->width;

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

	void setAnimation(const char* name) {
		animName = name;
		animIndex = animations[animName].index;
		frames = animations[animName].frames;
		speed = animations[animName].speed;
	}
};
