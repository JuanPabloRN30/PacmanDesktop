#include "Map.h"
#include "TextureManager.h"
#include "cleanup.h"

int lvl1[10][10] = {
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 5},
	{ 2, 8, 8, 8, 8, 8, 8, 8, 8, 8},
	{ 2, 8, 2, 8, 8, 8, 8, 3, 8, 8},
	{ 2, 8, 6, 4, 1, 1, 5, 8, 8, 8},
	{ 2, 8, 8, 2, 1, 8, 3, 8, 8, 8},
	{ 2, 8, 8, 2, 8, 1, 3, 8, 8, 8},
	{ 2, 8, 8, 6, 0, 0, 7, 8, 8, 8},
	{ 2, 8, 8, 8, 8, 8, 8, 1, 8, 8},
	{ 2, 8, 8, 8, 8, 8, 8, 8, 1, 8},
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 7},
};

Map::Map(const std::string& resPath, int width, int height)
{
	emptySpace = TextureManager::LoadTexture((resPath + "emptySpace.png").c_str()); // 9
	downWall = TextureManager::LoadTexture((resPath + "down_wall.png").c_str()); // 0
	upWall = TextureManager::LoadTexture((resPath + "up_wall.png").c_str()); // 1
	leftWall = TextureManager::LoadTexture((resPath + "left_wall.png").c_str()); // 2
	rightWall = TextureManager::LoadTexture((resPath + "right_wall.png").c_str()); // 3

	upLeftCorner = TextureManager::LoadTexture((resPath + "up_left_corner.png").c_str()); // 4
	upRightCorner = TextureManager::LoadTexture((resPath + "up_right_corner.png").c_str()); // 5
	downLeftCorner = TextureManager::LoadTexture((resPath + "down_left_corner.png").c_str()); // 6
	downRightCorner = TextureManager::LoadTexture((resPath + "down_right_corner.png").c_str()); // 7
	cookie = TextureManager::LoadTexture((resPath + "cookie.png").c_str()); // 8

	if (emptySpace == nullptr || downWall == nullptr || upWall == nullptr || leftWall == nullptr || rightWall == nullptr || cookie == nullptr) {
		throw "Problem loading texture";
	}

	xpos = 0;
	ypos = 0;
	this->width = width;
	this->height = height;

	loadMap(lvl1);

	srcRect.x = srcRect.y = 0;
	destRect.x = destRect.y = 0;
	srcRect.w = destRect.w = 60;
	srcRect.h = destRect.h = 60;
}

Map::~Map()
{
	cleanup(emptySpace, downWall, upWall, leftWall, rightWall);
	cleanup(upLeftCorner, upRightCorner, downLeftCorner, downRightCorner, cookie);
}

void Map::loadMap(int arr[10][10])
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = arr[i][j];
		}
	}
}

void Map::drawMap()
{
	int type = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			type = map[i][j];
			destRect.x = j * 60;
			destRect.y = i * 60;

			switch (type)
			{
				case 0:
					TextureManager::Draw(downWall, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 1:
					TextureManager::Draw(upWall, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 2:
					TextureManager::Draw(leftWall, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 3:
					TextureManager::Draw(rightWall, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 4:
					TextureManager::Draw(upLeftCorner, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 5:
					TextureManager::Draw(upRightCorner, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 6:
					TextureManager::Draw(downLeftCorner, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 7:
					TextureManager::Draw(downRightCorner, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 8:
					TextureManager::Draw(cookie, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				case 9:
					TextureManager::Draw(emptySpace, srcRect, destRect, NULL, SDL_FLIP_NONE);
					break;
				default:
					break;
			}
		}
	}
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}
