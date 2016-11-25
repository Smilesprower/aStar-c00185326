#pragma once
#include "SDL.h"
#include<vector>
#include <limits>

class Node {
public:
	Node(const Node &copy);
	Node(int index, int xPos, int yPos, int NODE_SIZE);
	~Node();
	bool open(int ID) const;
	bool close(int ID) const;
	int getCcost(int ID) const;
	int getFcost(int ID) const;
	Node* getPrevious(int ID) const;
	bool walkable() const;
	void setOpen(bool open, int ID);
	void setClose(bool close, int ID);
	void setFcost(int fCost, int ID);
	void setGcost(int gCost, int ID);
	void setPrevious(Node* previous, int ID);
	void setUp(bool walkable);
	void setUp(int ID);
	int getIndex();
	SDL_Rect getRect(SDL_Rect camera);
	SDL_Point getPosition();
	int getTileID();
	void setTileID(int ID);

private:
	const int MAX_NUM = 7;
	bool m_walkable;
	bool m_open;
	bool m_close;
	int m_fCost;
	int m_gCost;
	int m_index;
	Node* m_prevNode;
	int m_size;
	SDL_Rect m_rect;
	uint8_t m_tileID;
};