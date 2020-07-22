#include "Character.h"
#include "TextureManager.h"

int Character::directionAsInteger()
{
	return static_cast<typename std::underlying_type<Direction>::type>(direction);
}

Character:: Direction Character::getDirection()
{
	return direction;
}

SDL_Texture* Character::getImage()
{
	return image;
}

void Character::setDirection(Direction direction)
{
	this->direction = direction;
}

void Character::moveDown()
{
	int newY = dstRect.y + moveStep;
	if (canMove(newY, dstRect.h))
		dstRect.y = newY;
}

void Character::moveUp()
{
	int newY = dstRect.y - moveStep;
	if (canMove(newY, dstRect.h))
		dstRect.y = newY;
}

void Character::moveLeft()
{
	int newX = dstRect.x - moveStep;
	if (canMove(newX, dstRect.w))
		dstRect.x = newX;
}

void Character::moveRight()
{
	int newX = dstRect.x + moveStep;
	if (canMove(newX, dstRect.w))
		dstRect.x = newX;
}

bool Character::canMove(const int& value, const int& axisSize)
{
	return true;
}

void Character::calculateCurrentFrame()
{
}

void Character::draw()
{
	TextureManager::Draw(image, srcRect, dstRect, angle, spriteFlip);
}
