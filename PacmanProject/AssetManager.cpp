#include "AssetManager.h"

#include "SoundEffect.h"

void AssetManager::addFont(const char* id, const char* path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font* AssetManager::getFont(const char* id)
{
    return fonts[id];
}


void AssetManager::addSoundEffect(const char* id, const char* path)
{
    sound_effects.emplace(id, new SoundEffect(path));
}

SoundEffect* AssetManager::getSoundEffect(const char* id)
{
    return sound_effects[id];
}
