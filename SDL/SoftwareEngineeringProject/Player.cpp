#include "stdafx.h"
#include "Player.h"


Player::Player(SDL_Point pos, int size)
	: m_region(0)
	, m_rect{ pos.x * size, pos.y * size, size, size }
	, m_tileID{ 4, 1 }

{
}

Player::~Player()
{
}

void Player::update(float deltaTime, std::vector<Node*>* nodes, int worldHeight)
{
	m_timer += deltaTime;
	if (m_timer > 0.5f)
	{
		m_timer = 0;

		int tile = getTile();
		int random = rand() % OFFSET;
		if (random + OFFSET == Down && m_rect.y < worldHeight)
		{
			if (nodes->at(tile + 1000)->walkable())
			{
				m_tileID.x = Down;
				m_rect.y += m_rect.h;
			}
		}
		else if (random + OFFSET == Up && m_rect.y > 0)
		{
			if (nodes->at(tile - 1000)->walkable())
			{
				m_tileID.x = Up;
				m_rect.y -= m_rect.h;
			}
		}
		else if (random + OFFSET == Right && nodes->at(tile)->walkable())
		{
			if (nodes->at(tile + 1)->walkable())
			{
				m_tileID.x = Right;
				m_rect.x += m_rect.w;
			}
		}
		else if (random + OFFSET == Left && m_rect.x > 0 && nodes->at(tile)->walkable())
		{
			if (nodes->at(tile - 1)->walkable())
			{
				m_tileID.x = Left;
				m_rect.x -= m_rect.w;
			}
		}
	}
}

void Player::reset(SDL_Point pos)
{
	m_rect.x = pos.x * m_rect.w;
	m_rect.y = pos.y * m_rect.h;
}

SDL_Point Player::getTileID()
{
	return m_tileID;
}

SDL_Point Player::getPosition()
{
	return SDL_Point{ m_rect.x, m_rect.y };
}

SDL_Rect Player::getRect(SDL_Rect camera)
{
	return SDL_Rect{ m_rect.x - camera.x,m_rect.y - camera.y, m_rect.w, m_rect.h };
}

int Player::getTile()
{
	return (m_rect.x / m_rect.w) + (m_rect.y / m_rect.h) * 1000;
}
