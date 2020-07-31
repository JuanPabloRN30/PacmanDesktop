#pragma once

#include "ECS.h"

class ScoreComponent : public Component
{
public:
	int entityScore = 0;
	int score = 0;

	ScoreComponent() = default;

	ScoreComponent(int s) : score(s)
	{}

	~ScoreComponent(){}

	void addEntityScore(int es) {
		entityScore += es;
	}
};
