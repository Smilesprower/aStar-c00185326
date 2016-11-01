#pragma once
#include "SDL.h"
#include <limits>

class Node {
public:
	Node();
	Node(int x, int y, int size, int index, bool walkable);
	bool open() const;
	bool close() const;
	int getCcost() const;
	int getFcost() const;
	Node* getPrevious() const;
	bool walkable() const;
	void setOpen(bool open);
	void setClose(bool close);
	void setFcost(int fCost);
	void setGcost(int gCost);
	void setPrevious(Node* previous);
	void reset();
	int getIndex();
	SDL_Rect getRect();
	SDL_Point getPosition();
	SDL_Color getColor();
	void setColor(SDL_Color color);

	//overloads
	bool operator<(const Node&) const;
	bool operator==(const Node&) const;

private:
	bool m_walkable;
	bool m_open;
	bool m_close;
	int m_fCost;
	int m_gCost;
	int m_index;
	Node* m_prevNode;
	int m_size;
	SDL_Point m_position;
	SDL_Rect m_rect;
	SDL_Color m_color;

};