#include "stdafx.h"
#include "Node.h"

Node::Node(const Node & copy)
{
	m_open = copy.m_open;
	m_close = copy.m_open;
	m_fCost = copy.m_fCost;
	m_gCost = copy.m_gCost;
	m_rect = copy.m_rect;
	m_tileID = copy.m_tileID;
	m_prevNode = copy.m_prevNode;
	m_walkable = copy.m_walkable;
	m_index = copy.m_index;
}

Node::Node(int index, int xPos, int yPos, int NODESIZE)
	: m_index(index)
	, m_tileID(1)
	, m_rect { xPos* NODESIZE, yPos * NODESIZE, NODESIZE, NODESIZE }
{
}

Node::~Node()
{
	delete m_prevNode;
	m_prevNode = nullptr;
}

bool Node::open(int ID) const
{
	return m_open;
}

bool Node::close(int ID) const
{
	return m_close;
}

int Node::getCcost(int ID) const
{
	return m_gCost;
}

int Node::getFcost(int ID) const
{
	return m_fCost;
}

Node * Node::getPrevious(int ID) const
{
	return m_prevNode;
}

bool Node::walkable() const
{
	return m_walkable;
}

void Node::setOpen(bool open, int ID)
{
	m_open = open;
}

void Node::setClose(bool close, int ID)
{
	m_close = close;
}

void Node::setFcost(int fCost, int ID)
{
	m_fCost = fCost;
}

void Node::setGcost(int gCost, int ID)
{
	m_gCost = gCost;
}

void Node::setPrevious(Node * previous, int ID)
{
	m_prevNode = previous;
}

void Node::setUp(bool walkable)
{
	m_open = false;
	m_close = false;
	m_fCost = std::numeric_limits<int>::max();
	m_gCost = std::numeric_limits<int>::max();
	m_prevNode = 0;
	m_walkable = walkable;
	// May need to remove if drawing gets slow
	if (walkable)
		m_tileID = m_index % 3;
	else
		m_tileID = 5;
}
void Node::setUp(int ID)
{
	m_open = false;
	m_close = false;
	m_fCost = std::numeric_limits<int>::max();
	m_gCost = std::numeric_limits<int>::max();
	m_prevNode = 0;
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
	return SDL_Point{ m_rect.x, m_rect.y };
}
int Node::getTileID()
{
	return m_tileID;
}
void Node::setTileID(int ID)
{
	m_tileID = ID;
}