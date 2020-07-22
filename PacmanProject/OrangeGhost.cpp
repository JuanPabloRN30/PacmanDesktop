#include "OrangeGhost.h"
#include "TextureManager.h"
#include "cleanup.h"

OrangeGhost::OrangeGhost(const char* file, int x, int y, int width, int height)
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

	this->id = 1;
	this->direction = Direction::DOWN;
	this->moveStep = 1;

	calculateCurrentFrame();
}

OrangeGhost::~OrangeGhost()
{
	cleanup(image);
}

void OrangeGhost::move()
{
	direction = calculateRandomDirection();
	switch (direction)
	{
	case Direction::DOWN:
		moveDown();
		break;
	case Direction::UP:
		moveUp();
		break;
	case Direction::LEFT:
		moveLeft();
		break;
	case Direction::RIGHT:
		moveRight();
		break;
	default:
		// RAISE
		break;
	}
}