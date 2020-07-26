#pragma once
#include <string>

class Map
{
public:
	Map(const std::string& resPath, int width, int height);
	~Map();

	static void loadMap(std::string path, int sizeX, int sizeY);

private:
};
