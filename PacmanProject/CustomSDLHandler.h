#ifndef CustomSDLHandler_HEADER
#define CustomSDLHandler_HEADER

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class CustomSDLHandler
{
public:
	static void logSDLError(std::ostream& os, const std::string& msg);
	static SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren);
	static SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);
	static void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);
	static void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr);
	static void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip);
};

#endif