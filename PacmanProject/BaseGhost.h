#pragma once
#include "Character.h"

class BaseGhost : public Character
{
public:
	void calculateCurrentFrame() override;
	Direction calculateRandomDirection();

	protected:
		int id;
};
