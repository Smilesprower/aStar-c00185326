#include "stdafx.h"
#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int size)
	: m_pathCount(0)
	, m_active(false)
	, m_tileID{ Up, 1 }
	, m_size(size)
	, m_rect{0, 0, size, size}
	, m_collision(true)
{
}


Enemy::~Enemy()
{
}

void Enemy::setUp(SDL_Point pos, int m_nodesPerAxis)
{
	m_state = 0;
	m_collision = true;
	m_active = true;
	m_rect.x = pos.x * m_size;
	m_rect.y = pos.y * m_size;
	m_path.clear();
	m_tileID.x = Up;
}
void Enemy::update(float deltaTime, std::vector<Node*> *nodes, int * neighbourTiles)
{
	int currTileID = getTile();
	if (m_nextPath.x == m_rect.x && m_nextPath.y == m_rect.y)
	{
		if (m_pathCount < m_numOfPaths)
		{
			m_nextPath = m_path.at(m_pathCount);
			m_pathCount++;
		}
		else
		{
			m_state = 3;
		}
	}
	if (m_nextPath.x > m_rect.x)
	{
		if (!m_collision ||!nodes->at(currTileID + neighbourTiles[0])->getOccupied())
		{
			m_tileID.x = Right;
			m_rect.x += SPEED;
			nodes->at(currTileID + neighbourTiles[0])->setOccupied(true);
			nodes->at(currTileID)->setOccupied(false);
		}
	}
	else if (m_nextPath.x < m_rect.x)
	{
		if (!m_collision ||!nodes->at(currTileID + neighbourTiles[1])->getOccupied())
		{
			m_tileID.x = Left;
			m_rect.x -= SPEED;
			nodes->at(currTileID + neighbourTiles[1])->setOccupied(true);
			nodes->at(currTileID)->setOccupied(false);
		}
	}
	else if (m_nextPath.y < m_rect.y)
	{
		if (!m_collision || !nodes->at(currTileID + neighbourTiles[3])->getOccupied())
		{
			m_tileID.x = Up;
			m_rect.y -= SPEED;
			nodes->at(currTileID + neighbourTiles[3])->setOccupied(true);
			nodes->at(currTileID)->setOccupied(false);
		}
	}
	else if (m_nextPath.y > m_rect.y)
	{
		if (!m_collision || !nodes->at(currTileID + neighbourTiles[2])->getOccupied())
		{
			m_tileID.x = Down;
			m_rect.y += SPEED;
			nodes->at(currTileID + neighbourTiles[2])->setOccupied(true);
			nodes->at(currTileID)->setOccupied(false);
		}
	}
}
SDL_Rect Enemy::getRect(SDL_Rect camera)
{
	SDL_Rect temp{ m_rect.x - camera.x,m_rect.y - camera.y, m_rect.w, m_rect.h };
	return temp;
}

void Enemy::SetPath(std::vector<SDL_Point> path)
{
	m_path = path;
	m_numOfPaths = path.size();
	m_nextPath = path.at(1);
	m_pathCount = 1;
	if(m_state == 3)
		m_state = 2;
}

bool Enemy::getActive()
{
	return m_active;
}

void Enemy::setActive(bool active)
{
	m_active = active;
}

SDL_Point Enemy::getTileID()
{
	return m_tileID;
}

int Enemy::getTile()
{
	return (m_rect.x / m_rect.w) + (m_rect.y / m_rect.h) * 1000;
}

void Enemy::addPath(std::vector<SDL_Point> path)
{
	if(path.size() > 0)
		m_path.pop_back();	// path also includes starting point, remove duplicate
	m_path.insert(std::end(m_path), std::begin(path), std::end(path));
	m_numOfPaths = m_path.size();
}

int Enemy::getPathCount()
{
	return m_path.size();
}

int Enemy::getState()
{
	return m_state;
}

SDL_Point Enemy::getPosition()
{
	return SDL_Point{ m_rect.x, m_rect.y };
}

void Enemy::setState(int state)
{
	m_state = state;
}

void Enemy::setCollision(bool collision)
{
	m_collision = collision;
}

