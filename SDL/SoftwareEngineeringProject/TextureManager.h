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
	SDL_Texture* getTexture(int ID);
	bool TextureManager::load(std::string fileName, int id, SDL_Renderer* pRenderer);
private:

	static TextureManager *m_inst;
	std::map<int, SDL_Texture*> m_textureMap;

	TextureManager();
	~TextureManager();
};
