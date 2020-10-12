#include "Constants.h"

namespace Constants {
	const int ENTITY_WIDHT = 16;
	const int ENTITY_HEIGHT = 16;
	const int ENTITY_SCALE = 2;
	const int ENTITY_SPEED = 1;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	SDL_Color WHITE = { 255, 255, 255, 255 };

	// VIEWPORT
	SDL_Rect TOP_VIEWPORT = { 0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT >> 4 };
	SDL_Rect BOTTOM_VIEWPORT = { 0, TOP_VIEWPORT.h, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT - TOP_VIEWPORT.h};

	// FONT
	const char* MENU_FONT_ID = "font_50";
	const char* MENU_FONT_FILE = "VCR_OSD_MONO_1.001.ttf";
	const int MENU_FONT_SIZE = 50;
	const char* GAME_FONT_ID = "font_16";
	const char* GAME_FONT_FILE = "VCR_OSD_MONO_1.001.ttf";
	const int FONT_SIZE = 16;

	// LABEL
	const int PLAYER_ONE_SCORE_X = SCREEN_WIDTH >> 2;
	const int PLAYER_ONE_SCORE_Y = 0;
	const int HIGH_SCORE_X = SCREEN_WIDTH >> 1;
	const int HIGH_SCORE_Y = 0;

	// LIFES
	const int DEFAULT_N_LIFES = 3;

	// MAP
	const int MAP_SIZE_X = 13;
	const int MAP_SIZE_Y = 7;
	const int MAP_TILE_SIZE = 17;
	const int MAP_SCALE = 2;

	// COOKIE
	const int COOKIE_TILE_SIZE = 3;
	const int COOKIE_SCORE = 10;

	// POWER COOKIE
	const int POWER_COOKIE_TILE_SIZE = 3;
	const int POWER_COOKIE_SCORE = 50;

	// PACMAN
	const int UP_ANGLE = 0;
	const int LEFT_ANGLE = 90;
	const int DOWN_ANGLE = 180;
	const int RIGHT_ANGLE = 270;

	// GHOST
	const int GHOST_SCORE = 200;
	const int GHOST_MULTIPLIER = 2;

	// SOUNDS EFFECTS IDS
	const char* BEGINNING_ID = "beginning";
	const char* BEGINNING_FILE = "pacman_beginning.wav";
	const char* CHOMP_FILE = "pacman_chomp.wav";
	const char* CHOMP_ID = "chomp";
	const char* DEATH_FILE = "pacman_death.wav";
	const char* DEATH_ID = "death";
	const char* EAT_GHOST_FILE = "pacman_eatghost.wav";
	const char* EAT_GHOST_ID = "eat_ghost";
	const char* INTERMISSION_FILE = "pacman_intermission.wav";
	const char* INTERMISSION_ID = "intermission";

	// SCORE
	const char* HIGH_SCORE_FILE = "high_score.txt";

	// SPRITE
	const int PIXEL_SEPARATION = 1;
}