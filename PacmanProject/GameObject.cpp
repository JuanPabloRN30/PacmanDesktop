#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = 0;
	ypos = 0;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(objTexture);
}

void GameObject::update()
{
	xpos++;
	ypos++;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 60;
	srcRect.w = 60;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h * 1;
	destRect.w = srcRect.w * 1;
}

void GameObject::render()
{
	TextureManager::Draw(objTexture, srcRect, destRect, NULL, SDL_FLIP_NONE);
}
