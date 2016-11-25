#pragma once
#include "SDL.h"
class Player
{
public:
	enum Direction
	{
		Down = 4,
		Up = 5,
		Right = 6,
		Left = 7
	};

	Player(SDL_Point pos, int size);
	~Player();

	void update(float deltaTime);
	void reset(SDL_Point);
	SDL_Point getTileID();
	SDL_Rect getRect(SDL_Rect camera);
	int getTile();

private:
	int m_tileNo;
	int m_direction;
	int m_step;
	float m_timer;
	SDL_Rect m_rect;
	SDL_Point m_nextPath;
	SDL_Point m_tileID;
};

