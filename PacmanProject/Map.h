#pragma once
#include <string>
#include <map>
#include <utility>
#include "SDL.h"

class Map
{
public:
	Map(const char* mfp, int ms, int ts);
	~Map();

	std::map<std::pair<int, int>, SDL_Rect> loadColliders(std::string path, int nColliders);
	void loadMap(std::string path, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int xpos, int ypos);
	void addTileCollider(int srcX, int srcY, int xpos, int ypos, SDL_Rect collider);
	void addCookieTile(int xpos, int ypos);
	void addPowerCookieTile(int xpos, int ypos);

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};
