#include "Pacman.h"
#include "TextureManager.h"
#include "cleanup.h"

Pacman::Pacman(const char* file, int x, int y, int width, int height) {

	this->image = TextureManager::LoadTexture(file);

	if (image == nullptr) {
		throw "Problem loading texture";
	}

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = width;
	dstRect.h = height;

	this->direction = Direction::LEFT;
	this->moveStep = 20;

	calculateCurrentFrame();
}

Pacman::~Pacman(){
	cleanup(image);
}

void Pacman::calculateCurrentFrame()
{
	srcRect.x = 0;
	srcRect.y = srcRect.h * static_cast<int>(SDL_GetTicks() / 100 % 3) + 5;
}

void Pacman::move()
{
	switch (direction)
	{
	case Direction::DOWN:
		moveDown();
		angle = 180.0;
		break;
	case Direction::UP:
		moveUp();
		angle = 0;
		break;
	case Direction::LEFT:
		moveLeft();
		angle = 270.0;
		break;
	case Direction::RIGHT:
		moveRight();
		angle = 90.0;
		break;
	default:
		// RAISE
		break;
	}

	calculateCurrentFrame();
}