#include "stdafx.h"
#include "Node.h"


Node::Node()
{
}

Node::~Node()
{
	delete m_prevNode;
	m_prevNode = nullptr;
}

Node::Node(int x, int y, int size, int index, bool walkable)
	: m_walkable(walkable)
	, m_open(false)
	, m_close(false)
	, m_fCost(std::numeric_limits<int>::max())
	, m_gCost(std::numeric_limits<int>::max())
	, m_index(index)
	, m_prevNode(0)
	, m_size(size)
	, m_position(SDL_Point{ x * size, y * size })
	, m_rect(SDL_Rect{ m_position.x, m_position.y, m_size, m_size })
{
	if (index == 0)
		m_color = SDL_Color{ 0,255,255 };
	else if (walkable)
		m_color = SDL_Color{255,0,0};
	else
		m_color = SDL_Color{ 60,60,60 };
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

void Node::reset()
{
	m_prevNode = 0;
	m_fCost = std::numeric_limits<int>::max();
	m_gCost = std::numeric_limits<int>::max();
	m_close = false;
	m_open = false;
}
int Node::getIndex()
{
	return m_index;
}
SDL_Rect Node::getRect()
{
	return m_rect;
}
SDL_Point Node::getPosition()
{
	return m_position;
}
SDL_Color Node::getColor()
{
	return m_color;
}
void Node::setColor(SDL_Color color)
{
	m_color = color;
}
bool Node::operator<(const Node& n) const {
	return n.getFcost() < this->m_fCost;
}

bool Node::operator==(const Node& n) const {
	return n.getFcost() == this->m_fCost;
}