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


void SoundEffect::play() {
	Mix_PlayChannel(-1, sound, 0);
}