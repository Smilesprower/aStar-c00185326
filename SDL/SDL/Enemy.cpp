#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(int size)
	: m_pathCount(0)
	, m_start(false)
	, m_finished(false)
	, m_active(false)
	, m_tileID{ Up, 1 }
	, m_size(size)
	, m_rect{0, 0, size, size}
{
}


Enemy::~Enemy()
{
}

void Enemy::setUp(SDL_Point pos, int m_nodesPerAxis)
{
	m_active = true;
	m_startTileNo = pos.x + m_nodesPerAxis * pos.y;
	m_rect.x = pos.x * m_size;
	m_rect.y = pos.y * m_size;
}
void Enemy::update(float deltaTime)
{
	if (m_start)
	{
		if (m_nextPath.x == m_rect.x && m_nextPath.y == m_rect.y)
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
		if (m_nextPath.x > m_rect.x)
		{
			m_tileID.x = Right;
			m_rect.x += SPEED;
		}
		else if (m_nextPath.x < m_rect.x)
		{
			m_tileID.x = Left;
			m_rect.x -= SPEED;
		}
		else if (m_nextPath.y < m_rect.y)
		{
			m_tileID.x = Up;
			m_rect.y -= SPEED;
		}
		else if (m_nextPath.y > m_rect.y)
		{
			m_tileID.x = Down;
			m_rect.y += SPEED;
		}
	}
}
bool Enemy::start()
{
	return m_start;
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
	m_active = false;
	m_pathCount = 0;
	m_start = false;
	m_finished = false;
	m_tileID.x = Up;
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

