#include "BaseGhost.h"
#include <stdlib.h>
#include "SDL.h"

void BaseGhost::calculateCurrentFrame()
{
	int action = static_cast<int>(SDL_GetTicks() / 100 % 4);

	srcRect.x = id * srcRect.w + (id * 5);
	srcRect.y = srcRect.h * directionAsInteger() + (5 * directionAsInteger());

	// TODO: CHECK

	SDL_Rect ghost[4];

	SDL_Rect scaredBlueGhost;
	scaredBlueGhost.x = 4 * srcRect.w;
	scaredBlueGhost.y = 0;
	scaredBlueGhost.w = srcRect.w;
	scaredBlueGhost.h = srcRect.h;

	SDL_Rect scaredWhiteGhost;
	scaredWhiteGhost.x = 4 * srcRect.w;
	scaredWhiteGhost.y = 1 * srcRect.h + 5;
	scaredWhiteGhost.w = srcRect.w;
	scaredWhiteGhost.h = srcRect.h;
}

BaseGhost::Direction BaseGhost::calculateRandomDirection()
{
	int randDirectionPos = rand() % 4;
	Direction directions[4] = { Direction::DOWN, Direction::UP, Direction::LEFT, Direction::RIGHT };
	return directions[randDirectionPos];
}
