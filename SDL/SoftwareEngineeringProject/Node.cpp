#include "stdafx.h"
#include "Node.h"

Node::Node(int index, int xPos, int yPos, int NODESIZE)
	: m_index(index)
	, m_tileID(1)
	, m_rect { xPos* NODESIZE, yPos * NODESIZE, NODESIZE, NODESIZE }
	, m_occupied(false)
{
}
Node::~Node()
{
}
bool Node::walkable() const
{
	return m_walkable;
}
void Node::setUp(bool walkable)
{
	m_occupied = false;
	m_walkable = walkable;
	// May need to remove if drawing gets slow
	if (walkable)
		m_tileID = m_index % 3;
	else
		m_tileID = 5;
}
bool Node::getOccupied() const
{
	return m_occupied;
}
void Node::setOccupied(bool occupied)
{
	m_occupied = occupied;
}
int Node::getIndex() const
{
	return m_index;
}
SDL_Rect Node::getRect(SDL_Rect camera) const
{
	return SDL_Rect { m_rect.x - camera.x,m_rect.y - camera.y, m_rect.w, m_rect.h };
}
SDL_Point Node::getPosition() const
{
	return SDL_Point{ m_rect.x, m_rect.y };
}
int Node::getTileID() const
{
	return m_tileID;
}
void Node::setTileID(int ID)
{
	m_tileID = ID;
}