// SDL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

int main(int argc, char** argv) {

	Game* game = new Game();

	game->Initialize("DGPP Skelatol", 300, 100, 800, 600, SDL_WINDOW_INPUT_FOCUS);
	game->Loop();
	game->CleanUp();

	system("Pause");
	return 0;
}

//thread t1(&Process::run, Process((*(game)))); //Passing references
//t1.detach(); //detaches from SDL mainline

//class Process
//{
//public:
//	Process() {}
//	Process(const Game& game) : m_Game(game)
//	{
//
//	}
//	~Process() {};
//	void run()
//	{
//		while (m_Game.IsRunning())
//		{
//			//DEBUG_MSG("Thread Running");
//		}
//	}
//private:
//	Game m_Game;
//}