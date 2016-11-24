#include "stdafx.h"
#include "Node.h"


Node::Node(int index, int xPos, int yPos, int NODESIZE)
	: m_index(index)
	, m_size(NODESIZE)
	, m_tileID{1, 0}
	, m_position { xPos * m_size, yPos * m_size }
	, m_rect { m_position.x, m_position.y, m_size, m_size }
{
}

Node::~Node()
{
}

bool Node::open() const
{
	return m_open;
}

bool Node::close() const
{
	return m_close;
}

int Node::getCcost() const
{
	return m_gCost;
}

int Node::getFcost() const
{
	return m_fCost;
}

Node * Node::getPrevious() const
{
	return m_prevNode;
}

bool Node::walkable() const
{
	return m_walkable;
}

void Node::setOpen(bool open)
{
	m_open = open;
}

void Node::setClose(bool close)
{
	m_close = close;
}

void Node::setFcost(int fCost)
{
	m_fCost = fCost;
}

void Node::setGcost(int gCost)
{
	m_gCost = gCost;
}

void Node::setPrevious(Node * previous)
{
	m_prevNode = previous;
}

void Node::setUp(bool walkable)
{
	m_walkable = walkable;
	m_open = false;
	m_close = false;
	m_fCost = std::numeric_limits<int>::max();
	m_gCost = std::numeric_limits<int>::max();
	m_prevNode = 0;

	// May need to remove if drawing gets slow
	if (walkable)
		m_tileID.x = m_index % 3;
	else
		m_tileID.x = 5;
}
int Node::getIndex()
{
	return m_index;
}
SDL_Rect Node::getRect(SDL_Rect camera)
{
	SDL_Rect temp{ m_rect.x - camera.x,m_rect.y - camera.y, m_rect.w, m_rect.h };
	return temp;
}
SDL_Point Node::getPosition()
{
	return m_position;
}
SDL_Point Node::getTileID()
{
	return m_tileID;
}
void Node::setTileID(int ID)
{
	m_tileID.x = ID;
}
bool Node::operator<(const Node& n) const {
	return n.getFcost() < this->m_fCost;
}

bool Node::operator==(const Node& n) const {
	return n.getFcost() == this->m_fCost;
}