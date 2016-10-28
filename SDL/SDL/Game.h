#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Keyboard.h"
#include "LTimer.h"
#include "TextureManager.h"
#include "MenuScene.h"
#include "ResourceIdentifier.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void CleanUp();
	void Loop();

private:
	bool m_quit;
	unsigned int m_lastTime;

	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Event event;

	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
};
#endif