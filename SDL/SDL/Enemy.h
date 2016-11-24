#pragma once
#include "SDL.h"
#include <vector>
class Enemy
{
public:
	Enemy();
	~Enemy();

	void setUp(SDL_Point pos, int m_nodesPerAxis, int size);
	void update(float deltaTime);
	bool start();
	SDL_Color getColor();
	SDL_Rect getRect(SDL_Rect camera);
	void SetPath(std::vector<SDL_Point> path);
	int getStartNode();
	bool isFinished();
	void reset();

private:
	const int SPEED = 2;
	int m_startTileNo;
	int m_pathCount;
	bool m_start;
	bool m_finished;
	int m_numOfPaths;
	SDL_Color m_color;
	SDL_Rect m_rect;
	SDL_Point m_nextPath;
	std::vector<SDL_Point> m_path;
};

