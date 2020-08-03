#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include "ECS.h"
#include "TileComponent.h"
#include "ColliderComponent.h"
#include "ScoreComponent.h"
#include "PowerComponent.h"

extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{
}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			addTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				addTileCollider(x, y);
			}
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				addCookieTile(x, y);
			}else if (c == '2') {
				addPowerCookieTile(x, y);
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}

void Map::addTileCollider(int xpos, int ypos)
{
	auto& tcol(manager.addEntity());
	tcol.addComponent<ColliderComponent>("map", xpos * scaledSize, ypos * scaledSize, scaledSize, "collider.png");
	tcol.addGroup(Game::groupColliders);
}

void Map::addCookieTile(int xpos, int ypos)
{
	const int cookieTileSize = 3;
	int x = (scaledSize / 2) + (xpos * scaledSize);
	int y = (scaledSize / 2) + (ypos * scaledSize);


	auto& tcookie(manager.addEntity());
	tcookie.addComponent<ColliderComponent>("cookie", x, y, cookieTileSize * mapScale);
	tcookie.addComponent<TileComponent>(0, 0, x, y, cookieTileSize, mapScale, "cookie.png");
	tcookie.addComponent<ScoreComponent>(10);
	tcookie.addGroup(Game::groupCookies);
}

void Map::addPowerCookieTile(int xpos, int ypos)
{
	const int cookieTileSize = 3;
	int x = (scaledSize / 2) + (xpos * scaledSize);
	int y = (scaledSize / 2) + (ypos * scaledSize);


	auto& tcookie(manager.addEntity());
	tcookie.addComponent<ColliderComponent>("cookie", x, y, cookieTileSize * mapScale);
	tcookie.addComponent<TileComponent>(0, 0, x, y, cookieTileSize, mapScale, "cookiePower.png");
	tcookie.addComponent<ScoreComponent>(50);
	tcookie.addGroup(Game::groupPowerCookies);
}