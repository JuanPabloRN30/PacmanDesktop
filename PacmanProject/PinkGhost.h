#pragma once
#include "BaseGhost.h"

class PinkGhost : public BaseGhost
{
	public:
		PinkGhost(const char* file, int x, int y, int width, int height);
		~PinkGhost();
		void move();
};
