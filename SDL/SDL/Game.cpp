#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <thread>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

Game::Game() 
	: m_quit(false)
	, m_lastTime(LTimer::gameTime())
{
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

	// Load Scenes
	SceneManager::Instance()->addScene(new MenuScene(m_p_Renderer));

	return true;
}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);
	SceneManager::Instance()->render(m_p_Renderer);
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	unsigned int currentTime = LTimer::gameTime();
	float deltaTime = (currentTime - m_lastTime) / 1000.f;
	SceneManager::Instance()->update(deltaTime);
	m_lastTime = currentTime;
}

void Game::HandleEvents()
{
	Keyboard::Instance()->update();
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}
	SceneManager::Instance()->onEvent(m_quit);
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}

void Game::Loop()
{
	LTimer capTimer;
	int frameNum = 0;

	while (!m_quit)
	{ 
		capTimer.start();

		HandleEvents();
		Update();
		Render();

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}
