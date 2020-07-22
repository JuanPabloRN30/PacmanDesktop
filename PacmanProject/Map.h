#pragma once
#include "SDL.h"
#include <string>

class Map
{
public:
	Map(const std::string& resPath, int width, int height);
	~Map();

	void loadMap(int arr[10][10]);
	void drawMap();

private:
	SDL_Texture* emptySpace;
	SDL_Texture* downWall;
	SDL_Texture* upWall;
	SDL_Texture* leftWall;
	SDL_Texture* rightWall;
	SDL_Texture* upLeftCorner;
	SDL_Texture* upRightCorner;
	SDL_Texture* downRightCorner;
	SDL_Texture* downLeftCorner;
	SDL_Texture* cookie;
	SDL_Rect srcRect, destRect;
	int map[10][10];
};
