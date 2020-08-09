#pragma once

#include "SDL.h"

namespace Constants {
	extern const int ENTITY_WIDHT;
	extern const int ENTITY_HEIGHT;
	extern const int ENTITY_SCALE;
	extern const int ENTITY_SPEED;

	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;

	extern SDL_Color WHITE;

	// FONT
	extern const int FONT_SIZE;

	// LABEL
	extern const int PLAYER_ONE_SCORE_X;
	extern const int PLAYER_ONE_SCORE_Y;
	extern const int HIGH_SCORE_X;
	extern const int HIGH_SCORE_Y;

	// LIFES
	extern const int DEFAULT_N_LIFES;

	// MAP
	extern const int MAP_SIZE_X;
	extern const int MAP_SIZE_Y;
	extern const int MAP_TILE_SIZE;
	extern const int MAP_SCALE;

	// COOKIE
	extern const int COOKIE_TILE_SIZE;
	extern const int COOKIE_SCORE;

	// POWER COOKIE
	extern const int POWER_COOKIE_TILE_SIZE;
	extern const int POWER_COOKIE_SCORE;

	// PACMAN
	extern const int UP_ANGLE;
	extern const int LEFT_ANGLE;
	extern const int DOWN_ANGLE;
	extern const int RIGHT_ANGLE;

	// GHOST
	extern const int GHOST_SCORE;
	extern const int GHOST_MULTIPLIER;

	// SPRITE
	extern const int PIXEL_SEPARATION;
}