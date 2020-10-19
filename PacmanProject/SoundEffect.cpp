#include "SoundEffect.h"
#include "TextureManager.h"
#include "SDL_mixer.h"

SoundEffect::SoundEffect(const char* path)
{
	sound = Mix_LoadWAV(path);
	if (sound == nullptr)
	{
		TextureManager::LogSDLError(std::cout, "load sound effect");
		throw LoadSoundEffectException();
	}
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(sound);
}


void SoundEffect::play(int loops) {
	int channel = Mix_PlayChannel(-1, sound, loops);
	Mix_Volume(channel, MIX_MAX_VOLUME / 8);
}