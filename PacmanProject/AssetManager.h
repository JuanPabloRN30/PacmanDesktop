#pragma once

#include <map>
#include "ECS.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SoundEffect.h"

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager();

	void addFont(const char* id, const char* path, int fontSize);
	TTF_Font* getFont(const char* id);

	void addSoundEffect(const char* id, const char* path);
	SoundEffect* getSoundEffect(const char* id);

private:
	std::map<const char*, SDL_Texture*> textures;
	std::map<const char*, TTF_Font*> fonts;
	std::map<const char*, SoundEffect*> sound_effects;
};
