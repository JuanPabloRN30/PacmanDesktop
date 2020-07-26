#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map(const std::string& resPath, int width, int height)
{
}

Map::~Map()
{
}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 60, y * 60);
			mapFile.ignore();
		}
	}
	mapFile.close();
}
