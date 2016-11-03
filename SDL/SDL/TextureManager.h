#pragma once
#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"


class TextureManager
{
public:
	static TextureManager * Instance();

	// Load Texture
	bool TextureManager::load(std::string fileName, int id, SDL_Renderer* pRenderer);
	// Load Font
	bool TextureManager::loadFont(std::string message, int id, SDL_Renderer * pRenderer);


	// Draw 
	void draw(int id, int x, int y, int w, int h, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawMessage(int id, int x, int y, int w, int h, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:

	static TextureManager *m_inst;
	std::map<int, SDL_Texture*> m_textureMap;

	TextureManager();
	~TextureManager();
};
