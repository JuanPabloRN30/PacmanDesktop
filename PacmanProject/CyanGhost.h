#pragma once
#include "BaseGhost.h"

class CyanGhost : public BaseGhost
{
	public:
		CyanGhost(const char* file, int x, int y, int width, int height);
		~CyanGhost();
		void move();
};
