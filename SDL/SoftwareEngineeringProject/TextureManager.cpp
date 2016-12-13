#include "stdafx.h"
#include "TextureManager.h"
#include "SDL_image.h"

TextureManager * TextureManager::m_inst = nullptr;
TextureManager * TextureManager::Instance()
{
	if (!m_inst)
	{
		m_inst = new TextureManager();
	}
	return m_inst;
}

SDL_Texture * TextureManager::getTexture(int ID)
{
	return m_textureMap[ID];
}


bool TextureManager::load(std::string fileName, int id, SDL_Renderer * pRenderer)
{

	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0)
	{
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	if (!m_textureMap.empty())
	{
		for (std::map<int, SDL_Texture *>::iterator it = m_textureMap.begin(); it != m_textureMap.end(); ++it)
		{
			SDL_DestroyTexture(it->second);
			(it->second) = nullptr;
		}
		m_textureMap.clear();
	}
}
