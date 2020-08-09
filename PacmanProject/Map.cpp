#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "ECS.h"
#include "TileComponent.h"
#include "ColliderComponent.h"
#include "ScoreComponent.h"
#include "Constants.h"

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

	// tiles
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

	// colliders
	std::string collidersPath = "colliders.txt";
	int nColliders = 7;
	int tileIDX, tileIDY;
	std::map<std::pair<int, int>, SDL_Rect> colliders = loadColliders(collidersPath, nColliders);
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			tileIDY = atoi(&c);
			srcY = tileIDY * tileSize;
			mapFile.get(c);
			tileIDX = atoi(&c);
			srcX = tileIDX * tileSize;
			if (srcX != 0 || srcY != 0) {
				addTileCollider(srcX, srcY, x * scaledSize, y * scaledSize, colliders[{tileIDY, tileIDX}]);
			}
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	// cookies and powers
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

std::map<std::pair<int , int>, SDL_Rect> Map::loadColliders(std::string path, int nColliders)
{
	char comma;
	int srcX, srcY, tilePosition;
	int x, y;
	int w, h;
	std::fstream colliderFile;
	colliderFile.open(path);

	std::map<std::pair<int, int>, SDL_Rect> colliderInfo;
	std::string line;
	for (int i = 0; i < nColliders; i++) {
		std::getline(colliderFile, line);
		std::stringstream ss(line);
		ss >> tilePosition;
		srcY = tilePosition / 10;
		srcX = tilePosition % 10;
		std::getline(colliderFile, line);
		std::stringstream ss1(line);
		ss1 >> x >> comma >> y >> comma >> w >> comma >> h;
		colliderInfo[{srcY, srcX}] = { x * mapScale, y * mapScale, w * mapScale, h * mapScale};
	}

	colliderFile.close();

	return colliderInfo;
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}

void Map::addTileCollider(int srcX, int srcY, int xpos, int ypos, SDL_Rect collider)
{
	auto& tcol(manager.addEntity());
	tcol.addComponent<ColliderComponent>("map", srcX, srcY, xpos, ypos, tileSize, mapFilePath, collider);
	tcol.addGroup(Game::groupColliders);
}

void Map::addCookieTile(int xpos, int ypos)
{
	int x = (scaledSize / 2) + (xpos * scaledSize);
	int y = (scaledSize / 2) + (ypos * scaledSize);


	auto& tcookie(manager.addEntity());
	tcookie.addComponent<ColliderComponent>("cookie", x, y, Constants::COOKIE_TILE_SIZE * mapScale);
	tcookie.addComponent<TileComponent>(0, 0, x, y, Constants::COOKIE_TILE_SIZE, mapScale, "cookie.png");
	tcookie.addComponent<ScoreComponent>(10);
	tcookie.addGroup(Game::groupCookies);
}

void Map::addPowerCookieTile(int xpos, int ypos)
{
	int x = (scaledSize / 2) + (xpos * scaledSize);
	int y = (scaledSize / 2) + (ypos * scaledSize);

	auto& tcookie(manager.addEntity());
	tcookie.addComponent<ColliderComponent>("cookie", x, y, Constants::COOKIE_TILE_SIZE * mapScale);
	tcookie.addComponent<TileComponent>(0, 0, x, y, Constants::COOKIE_TILE_SIZE, mapScale, "cookiePower.png");
	tcookie.addComponent<ScoreComponent>(50);
	tcookie.addGroup(Game::groupPowerCookies);
}