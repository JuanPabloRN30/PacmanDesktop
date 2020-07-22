#pragma once
#include "Game.h"
#include <iostream>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle, SDL_RendererFlip flip);
	static void LogSDLError(std::ostream& os, const std::string& msg);

};