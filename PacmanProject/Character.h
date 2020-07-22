#pragma once
#include "SDL.h"

class Character
{
	public:
		enum class Direction { DOWN = 0, UP = 1, LEFT = 2, RIGHT = 3 };
		int directionAsInteger();
		Direction getDirection();
		SDL_Texture* getImage();
		void setDirection(Direction direction);
		virtual void move() = 0;
		virtual void calculateCurrentFrame();
		void draw();
	protected:
		int moveStep;
		double angle;

		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
		SDL_Texture* image;
		SDL_Rect srcRect, dstRect;
		Direction direction;
	protected:
		void moveDown();
		void moveUp();
		void moveLeft();
		void moveRight();
		bool canMove(const int& value,const int& axisSize);
};