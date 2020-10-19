#pragma once

#include <map>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Constants.h"
#include "SoundEffect.h"

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager();

	void addFont(const char* id, const char* path, int fontSize = Constants::FONT_SIZE);
	TTF_Font* getFont(const char* id);

	void addSoundEffect(const char* id, const char* path);
	SoundEffect* getSoundEffect(const char* id);

private:
	std::map<const char*, SDL_Texture*> textures;
	std::map<const char*, TTF_Font*> fonts;
	std::map<const char*, SoundEffect*> sound_effects;
};
