#pragma once
#include <list>
#include <iostream>
#include <queue>
#include "Node.h"
#include <vector>
#include <map>

class AStar {
public:
	class NodeSearchCostComparer {
	public:
		bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
			return p1.first > p2.first;
		}
	};
	AStar();
	AStar(int numOfNodes, int numOfNodesPerAxis, int nodeDimensions);
	~AStar();

	std::vector<SDL_Point> findPath(std::vector<Node*> *nodes, int startIndex, int goalIndex, int ID);
	int getHeuristic(Node* currentNode, Node* goalNode);
	int getNeighbourIndex(Node * current, int neighbourIndex);

private:
	// Critical data of the Node
	////////////////////////////////////////
	struct Data
	{
		bool m_open;
		bool m_close;
		int m_fCost;
		int m_gCost;
		Node* m_prevNode;
		Data(bool open = false, bool closed = false, int fCost = std::numeric_limits<int>::max(), int gCost = std::numeric_limits<int>::max(), Node* prevNode = 0)
			: m_open(open)
			, m_close(closed)
			, m_fCost(fCost)
			, m_gCost(gCost)
			, m_prevNode(prevNode)
		{
		}
	};

	int m_numOfNodes;
	int m_numOfNodesPerAxis;
	int m_nodeDimensions;
	int m_neighbourNode[4];
	std::vector<SDL_Point> createPath(Node* goalNode, Node * startNode, std::map<Node*, Data> * nodeData);
};