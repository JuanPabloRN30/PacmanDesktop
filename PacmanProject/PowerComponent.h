#pragma once

#include "ECS.h"

class PowerComponent : public Component
{
public:
	bool on = true;

	PowerComponent() = default;
	~PowerComponent(){}

	bool isOn() {
		return on;
	}

	void turnOn() {
		on = true;
	}

	void turnOff() {
		on = false;
	}
};
