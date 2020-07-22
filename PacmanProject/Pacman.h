#pragma once
#include "Character.h"

class Pacman : public Character
{
	public:

		Pacman(const char* file, int x, int y, int width, int height);
		~Pacman();
		void calculateCurrentFrame();
		void move();
};
