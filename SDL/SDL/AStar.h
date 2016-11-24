#pragma once
#include <list>
#include <iostream>
#include <queue>
#include "Node.h"
#include <vector>

class AStar {
	class NodeSearchCostComparer {
	public:
		bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
			return p1.first > p2.first;
		}
	};

public:
	AStar();
	AStar(int numOfNodes, int numOfNodesPerAxis, int nodeDimensions);
	~AStar();

	std::vector<SDL_Point> findPath(std::vector<Node*> m_nodes, int startIndex, int goalIndex);
	int getHeuristic(Node* currentNode, Node* goalNode);
	int getNeighbourIndex(Node * current, int neighbourIndex);

private:
	int m_numOfNodes;
	int m_numOfNodesPerAxis;
	int m_nodeDimensions;

	int m_neighbourNode[4];
	std::vector<SDL_Point> createPath(Node* goalNode, Node * startNode);
};