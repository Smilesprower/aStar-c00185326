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

void TextureManager::draw(int id, int x, int y, int w, int h,  SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;

	destRect.x = x;
	destRect.y = y;
	// Source Rect is the part of texture we want to draw.
	// Dest Rect is where we want to draw the rectangle.
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
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
