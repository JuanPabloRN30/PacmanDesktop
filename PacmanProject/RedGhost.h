#pragma once
#include "BaseGhost.h"

class RedGhost : public BaseGhost
{
	public:
		RedGhost(const char* file, int x, int y, int width, int height);
		~RedGhost();
		void move();
};
