#pragma once
#include "SDL.h"
#include <vector>
class Enemy
{
public:
	Enemy(int size);
	~Enemy();

	enum Direction
	{
		Down,
		Up,
		Right,
		Left
	};


	void setUp(SDL_Point pos, int m_nodesPerAxis, int size);
	void update(float deltaTime);
	bool start();
	SDL_Rect getRect(SDL_Rect camera);
	void SetPath(std::vector<SDL_Point> path);
	int getStartNode();
	bool isFinished();
	void reset();
	bool getActive();
	void setActive(bool active);
	SDL_Point getTileID();

private:
	const int SPEED = 20;
	int m_startTileNo;
	int m_pathCount;
	bool m_start;
	bool m_finished;
	int m_numOfPaths;
	bool m_active;
	int m_size;
	SDL_Rect m_rect;
	SDL_Point m_nextPath;
	SDL_Point m_tileID;
	std::vector<SDL_Point> m_path;
};

