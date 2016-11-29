#pragma once
#include "SDL.h"
#include<vector>
#include <limits>

class Node {
public:
	Node(int index, int xPos, int yPos, int NODE_SIZE);
	~Node();

	SDL_Rect getRect(SDL_Rect camera) const;
	SDL_Point getPosition() const;
	bool walkable() const;
	int getIndex() const;
	int getTileID() const;
	void setTileID(int ID);
	void setUp(bool walkable);

private:
	bool m_walkable, m_open, m_close;
	int m_fCost, m_gCost, m_index, m_size;
	Node* m_prevNode;
	SDL_Rect m_rect;
	uint8_t m_tileID;
};