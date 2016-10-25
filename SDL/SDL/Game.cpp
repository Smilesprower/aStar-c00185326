#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <thread>

Game::Game() : m_running(false)
{
	SceneManager::Instance()->addScene(new MenuScene());
	SceneManager::Instance()->changeScene(Scenes::MenuScene);
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	m_running = true;

	return true;
}



void Game::LoadContent()
{
	// For the moment this will load all Textures;
	if (!TextureManager::Instance()->load("assets/1.png", Textures::Player, m_p_Renderer))
	{
			DEBUG_MSG("Texture Query Failed");
	}
	if (!TextureManager::Instance()->load("assets/2.png", Textures::Level, m_p_Renderer))
	{
			DEBUG_MSG("Texture Query Failed");
	}
}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);
	SceneManager::Instance()->render(m_p_Renderer);
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	//DEBUG_MSG("Updating....");
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						m_running = false;
						break;
				}
				//case SDLK_UP:
				//	DEBUG_MSG("Up Key Pressed");
				//	SDL_SetRenderDrawColor(m_p_Renderer, 255, 0, 0, 255);
				//	break;
				//case SDLK_DOWN:
				//	DEBUG_MSG("Down Key Pressed");
				//	SDL_SetRenderDrawColor(m_p_Renderer, 0, 255, 0, 255);
				//	break;
				//case SDLK_LEFT:
				//	DEBUG_MSG("Left Key Pressed");
				//	SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 255, 255);
				//	break;
				//case SDLK_RIGHT:
				//	DEBUG_MSG("Right Key Pressed");
				//	SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
				//	break;
				//default:
				//	SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
				//	break;
				//}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");
	TextureManager::Instance()->cleanUpAll();
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}