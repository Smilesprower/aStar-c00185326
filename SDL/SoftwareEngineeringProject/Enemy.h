#pragma once
#include "SDL.h"
#include "Node.h"
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


	void setUp(SDL_Point pos, int m_nodesPerAxis);
	void update(float deltaTime, std::vector<Node*> *nodes, int * neighbourTiles);
	SDL_Rect getRect(SDL_Rect camera);
	void SetPath(std::vector<SDL_Point> path);
	bool getActive();
	void setActive(bool active);
	SDL_Point getTileID();
	int getTile();
	void addPath(std::vector<SDL_Point> m_path);
	int getPathCount();
	int getState();
	SDL_Point getPosition();
	void setState(int state);
	void setCollision(bool collision);
	

private:
	const int SPEED = 20;
	int m_pathCount;
	int m_numOfPaths;
	bool m_active;
	bool m_collision;
	int m_size;
	int m_state;
	SDL_Rect m_rect;
	SDL_Point m_nextPath;
	SDL_Point m_tileID;
	std::vector<SDL_Point> m_path;
};

