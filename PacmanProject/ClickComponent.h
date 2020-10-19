#pragma once
#include "ECS.h"
#include "Window.h"
#include "UILabel.h"
class ClickComponent : public Component
{
public:
	UILabel* label;
	SDL_Rect viewport;

	int xpos;
	int ypos;

	ClickComponent() {
		viewport = { 0, 0, 0, 0 };
		xpos = ypos = -1;
		label = nullptr;
	}
	ClickComponent(SDL_Rect mViewport) : viewport(mViewport)
	{
		xpos = ypos = -1;
		label = nullptr;
	}

	void init() override {
		label = &entity->getComponent<UILabel>();
	}

	void update() override {
		if (Window::_event.type == SDL_MOUSEBUTTONUP) {
			if (Window::_event.button.button == SDL_BUTTON_LEFT) {
				xpos = -1;
				ypos = -1;
			}
		}

		if (Window::_event.type == SDL_MOUSEBUTTONDOWN) {
			if (Window::_event.button.button == SDL_BUTTON_LEFT) {
				xpos = Window::_event.button.x;
				ypos = Window::_event.button.y;
				std::cout << xpos << " " << ypos << std::endl;
			}
		}
	}

	bool isClicked() {
		return (
			xpos >= label->position.x + viewport.x
			&& xpos < label->position.x + label->position.w + viewport.x
			&& ypos >= label->position.y + viewport.y
			&& ypos < label->position.y + label->position.h + viewport.y
		);
	}
};
