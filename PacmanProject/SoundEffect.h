#pragma once

#include <exception>
#include <SDL_mixer.h>

class LoadSoundEffectException : public std::exception {};

class SoundEffect
{
public:
	SoundEffect(const char* path);
	~SoundEffect();

	void play(int loops = 0);

private:
	Mix_Chunk* sound;

	
};

