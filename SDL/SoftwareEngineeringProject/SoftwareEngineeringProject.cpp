// SoftwareEngineeringProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define SDL_MAIN_HANDLED
#pragma comment(lib,"SDL2.lib") 
#pragma comment(lib, "SDL2_image.lib")

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

int main(int argc, char** argv) {

	Game* game = new Game();

	game->Initialize("A-Star*", 300, 100, 800, 600, SDL_WINDOW_INPUT_FOCUS);
	game->Loop();
	game->CleanUp();

	system("Pause");
	return 0;
}