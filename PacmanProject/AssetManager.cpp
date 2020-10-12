#include "AssetManager.h"

#include "Constants.h"
#include "SoundEffect.h"

#include <iostream>

void AssetManager::addFont(const char* id, const char* path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font* AssetManager::getFont(const char* id)
{
    if (fonts.find(id) != fonts.end()) return fonts[id];
    return nullptr;
}


void AssetManager::addSoundEffect(const char* id, const char* path)
{
    sound_effects.emplace(id, new SoundEffect(path));
}

SoundEffect* AssetManager::getSoundEffect(const char* id)
{
    return sound_effects[id];
}
