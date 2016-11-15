#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
	: m_color(SDL_Color{ 0,0,255})
	, m_pathCount(0)
	, m_start(false)
	, m_finished(false)
{
}


Enemy::~Enemy()
{
}

void Enemy::setUp(SDL_Point pos, int m_nodesPerAxis, int size)
{
	m_startTileNo = pos.x + m_nodesPerAxis * pos.y;
	m_bounds.x = pos.x * size;
	m_bounds.y = pos.y * size;
	m_bounds.h = size;
	m_bounds.w = size;
}
void Enemy::update(float deltaTime)
{
	if (m_start)
	{
		if (m_nextPath.x == m_bounds.x && m_nextPath.y == m_bounds.y)
		{
			if (m_pathCount < m_numOfPaths)
			{
				m_nextPath = m_path.at(m_pathCount);
				m_pathCount++;
			}
			else
			{
				m_finished = true;
			}
		}
		if (m_nextPath.x > m_bounds.x)
			m_bounds.x += SPEED * deltaTime;
		else if (m_nextPath.x < m_bounds.x)
			m_bounds.x -= SPEED * deltaTime;
		else if (m_nextPath.y < m_bounds.y)
			m_bounds.y -= SPEED * deltaTime;
		else if (m_nextPath.y > m_bounds.y)
			m_bounds.y += SPEED * deltaTime;
	}
}
bool Enemy::start()
{
	return m_start;
}
SDL_Color Enemy::getColor()
{
	return m_color;
}
SDL_Rect Enemy::getRect()
{
	return m_bounds;
}

void Enemy::SetPath(std::vector<SDL_Point> path)
{
	m_path = path;
	m_numOfPaths = path.size();
	m_nextPath = path.at(0);
	m_pathCount++;
	m_start = true;
}

int Enemy::getStartNode()
{
	return m_startTileNo;
}

bool Enemy::isFinished()
{
	return m_finished;
}

void Enemy::reset()
{
	m_pathCount = 0;
	m_start = false;
	m_finished = false;
}

