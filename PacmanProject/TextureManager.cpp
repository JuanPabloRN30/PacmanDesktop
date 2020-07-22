#include "TextureManager.h"
#include "SDL_image.h"

/**
* Log an SDL error with some error message to the output stream of our choice
* @param fileName The output stream to write the message to
*/
SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Texture* text = IMG_LoadTexture(Game::renderer, fileName);
	if (text == nullptr) {
		TextureManager::LogSDLError(std::cout, "LoadTexture");
	}
	return text;
}

/**
* Log an SDL error with some error message to the output stream of our choice
* @param tex The output stream to write the message to
* @param src The error message to write, format will be msg error: SDL_GetError()
* @param dst The error message to write, format will be msg error: SDL_GetError()
* @param flip The error message to write, format will be msg error: SDL_GetError()
*/
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, angle, NULL, flip);
}


/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void TextureManager::LogSDLError(std::ostream& os, const std::string& msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}