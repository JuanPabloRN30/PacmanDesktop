#include "PinkGhost.h"
#include "TextureManager.h"
#include "cleanup.h"

PinkGhost::PinkGhost(const char* file, int x, int y, int width, int height)
{
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

	this->id = 2;
	this->direction = Direction::DOWN;
	this->moveStep = 1;

	calculateCurrentFrame();
}

PinkGhost::~PinkGhost()
{
	cleanup(image);
}

void PinkGhost::move()
{
	direction = calculateRandomDirection();
	switch (direction)
	{
	case Direction::DOWN:
		moveDown();
		return;
	case Direction::UP:
		moveUp();
		return;
	case Direction::LEFT:
		moveLeft();
		return;
	case Direction::RIGHT:
		moveRight();
		return;
	default:
		// RAISE
		break;
	}

	calculateCurrentFrame();
}