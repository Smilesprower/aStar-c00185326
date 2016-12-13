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
	bool getOccupied() const;
	void setOccupied(bool occupied);



private:
	bool m_walkable;
	bool m_occupied;
	int m_index, m_size;
	SDL_Rect m_rect;
	uint8_t m_tileID;
};