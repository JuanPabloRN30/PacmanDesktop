#pragma once
#include "BaseGhost.h"
class OrangeGhost : public BaseGhost
{
	public:
		OrangeGhost(const char* file, int x, int y, int width, int height);
		~OrangeGhost();
		void move();
};