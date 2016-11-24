#pragma once
#include "SDL.h"
#include <limits>

class Node {
public:
	Node(int index, int xPos, int yPos, int NODE_SIZE);
	~Node();
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
	void setUp(bool walkable);
	int getIndex();
	SDL_Rect getRect(SDL_Rect camera);
	SDL_Point getPosition();
	SDL_Point getTileID();
	void setTileID(int ID);

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
	SDL_Point m_tileID;
};