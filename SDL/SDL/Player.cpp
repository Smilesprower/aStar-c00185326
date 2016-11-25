#include "stdafx.h"
#include "Player.h"


Player::Player(SDL_Point pos, int size)
	: m_rect{ pos.x * size, pos.y * size, size, size }
	, m_tileID{ 4, 1 }
{
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer > 0.2f)
	{
		m_timer = 0;
		m_rect.y += m_rect.h;
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

SDL_Rect Player::getRect(SDL_Rect camera)
{
	return SDL_Rect{ m_rect.x - camera.x,m_rect.y - camera.y, m_rect.w, m_rect.h };
}

int Player::getTile()
{
	return (m_rect.x / m_rect.w) + (m_rect.y / m_rect.h) * 1000;
}
