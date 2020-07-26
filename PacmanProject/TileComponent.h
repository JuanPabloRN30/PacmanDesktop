#pragma once

#include "ECS.h"
#include "SDL.h"
#include "cleanup.h"
#include "TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	TileComponent() = default;

	~TileComponent() {
		cleanup(texture);
	}


	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {

		texture = TextureManager::LoadTexture(path);
		
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 60;		

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 60;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, NULL, SDL_FLIP_NONE);
	}
};
