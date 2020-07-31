#include "AssetManager.h"

void AssetManager::addFont(const char* id, const char* path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font* AssetManager::getFont(const char* id)
{
    return fonts[id];
}
