#include "stdafx.h"
#include "Node.h"


Node::Node(int index, int xPos, int yPos, int NODESIZE)
	: m_index(index)
	, m_tileID(1)
	, m_rect { xPos* NODESIZE, yPos * NODESIZE, NODESIZE, NODESIZE }
	, m_close(MAX_NUM)
	, m_open(MAX_NUM)
	, m_fCost(MAX_NUM)
	, m_gCost(MAX_NUM)
	, m_prevNode(MAX_NUM)
{
}

Node::~Node()
{
}

bool Node::open(int ID) const
{
	return m_open[ID];
}

bool Node::close(int ID) const
{
	return m_close[ID];
}

int Node::getCcost(int ID) const
{
	return m_gCost[ID];
}

int Node::getFcost(int ID) const
{
	return m_fCost[ID];
}

Node * Node::getPrevious(int ID) const
{
	return m_prevNode[ID];
}

bool Node::walkable() const
{
	return m_walkable;
}

void Node::setOpen(bool open, int ID)
{
	m_open[ID] = open;
}

void Node::setClose(bool close, int ID)
{
	m_close[ID] = close;
}

void Node::setFcost(int fCost, int ID)
{
	m_fCost[ID] = fCost;
}

void Node::setGcost(int gCost, int ID)
{
	m_gCost[ID] = gCost;
}

void Node::setPrevious(Node * previous, int ID)
{
	m_prevNode[ID] = previous;
}

void Node::setUp(bool walkable)
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		m_open[i] = false;
		m_close[i] = false;
		m_fCost[i] = std::numeric_limits<int>::max();
		m_gCost[i] = std::numeric_limits<int>::max();
		m_prevNode[i] = 0;
	}
	m_walkable = walkable;
	// May need to remove if drawing gets slow
	if (walkable)
		m_tileID = m_index % 3;
	else
		m_tileID = 5;
}
void Node::setUp(bool walkable, int ID)
{
	m_open[ID] = false;
	m_close[ID] = false;
	m_fCost[ID] = std::numeric_limits<int>::max();
	m_gCost[ID] = std::numeric_limits<int>::max();
	m_prevNode[ID] = 0;

	m_walkable = walkable;
	// May need to remove if drawing gets slow
	if (walkable)
	m_tileID = m_index % 3;
	else
	m_tileID = 5;
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