#include "stdafx.h"
#include "AStar.h"


const int NEIGHBOUR_COUNT = 4;
const int COST = 20;


AStar::AStar()
{
}

AStar::AStar(int numOfNodes, int numOfNodesPerAxis)
	: m_numOfNodes(numOfNodes)
	, m_numOfNodesPerAxis(numOfNodesPerAxis)
{
	m_neighbourNode[0] = 1; // Right
	m_neighbourNode[1] = -1; // Left
	m_neighbourNode[2] = numOfNodesPerAxis; // Down
	m_neighbourNode[3] = -numOfNodesPerAxis; // Up
}

AStar::~AStar()
{
}

std::vector<SDL_Point> AStar::findPath(std::vector<Node*> *m_nodes, int startIndex, int goalIndex)
{
	std::map<Node*, Data> nodeData;

	Node* start = m_nodes->at(startIndex);
	Node* goal = m_nodes->at(goalIndex);

	if (start != 0 && goal != 0)
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, NodeSearchCostComparer> openset;
		nodeData[start].m_gCost = 0;
		nodeData[start].m_fCost = getHeuristic(start, goal);
		nodeData[start].m_open = true;

		openset.push(std::pair<int, int>(nodeData[start].m_fCost, startIndex));

		int previousCost = 0;

		while (openset.size() != 0)
		{
			Node* current = m_nodes->at(openset.top().second);
			openset.pop();
			if (current == goal)
			{
				return createPath(goal, start, &nodeData);
			}
			nodeData[current].m_open = false;
			nodeData[current].m_close = true;

			for (int i = 0; i < NEIGHBOUR_COUNT; i++)
			{
				int neighbourIndex = getNeighbourIndex(current, i);

				Node* neighbour;
				if (neighbourIndex == -1)
				{
					neighbour = 0;
				}
				else
				{
					neighbour = m_nodes->at(neighbourIndex);
				}

				if (neighbour == 0 || nodeData[neighbour].m_close == true
					|| neighbour == nodeData[current].m_prevNode
					|| neighbour->walkable() == false)
				{
					continue;
				}

				int tenativeGCost = nodeData[current].m_gCost + COST;
				if (tenativeGCost <= nodeData[neighbour].m_gCost)
				{
					nodeData[neighbour].m_prevNode = current;
					nodeData[neighbour].m_gCost = tenativeGCost;
					nodeData[neighbour].m_fCost = getHeuristic(neighbour, goal);
				}

				if (nodeData[neighbour].m_open == false)
				{

					//neighbour->setTileID(3);
					nodeData[neighbour].m_open = true;
					openset.push(std::pair<int, int>(nodeData[neighbour].m_fCost, neighbourIndex));
				}
				previousCost = tenativeGCost;
			}
			if (openset.size() == 0)
				std::cout << "Couldn't find path." << std::endl;
		}
	}
	return std::vector<SDL_Point>();
}

int AStar::getHeuristic(Node * n1, Node * n2)
{

	// Euclidean distance
	//int dx = abs(n1->getPosition().x - n2->getPosition().x);
	//int dy = abs(n1->getPosition().y - n2->getPosition().y);
	//return (dx * dx + dy * dy);

	// Manhattan distance
	return abs(n1->getPosition().x - n2->getPosition().x) + abs(n1->getPosition().y - n2->getPosition().y);

	// Chebyshev Distance - Awful on massive grids
	//return std::max(n1->getPosition().x - n2->getPosition().x, n1->getPosition().y - n2->getPosition().y);
}

/*
1D Vector Horizontal Check
Check that edge index's +1 or -1 are not allowed to be valid,
because this wraps them to the other side of the screen.
[9] = right edge node. [9 + 1] = left side node.
*/
int AStar::getNeighbourIndex(Node * current, int neighbourIndex)
{
	int index = current->getIndex() + m_neighbourNode[neighbourIndex];

	if (neighbourIndex == 0 && index % m_numOfNodesPerAxis == 0
		|| neighbourIndex == 1 && index % m_numOfNodesPerAxis == m_numOfNodesPerAxis - 1
		|| index < 0 || index > m_numOfNodes - 1)
	{
		return -1;
	}

	return index;
}

int * AStar::getNeighbours()
{
	return m_neighbourNode;
}

std::vector<SDL_Point> AStar::createPath(Node * goalNode, Node * startNode, std::map<Node*, Data> * nodeData)
{
	std::vector<SDL_Point> path;

	for (Node* previous = goalNode; previous != 0; previous = nodeData->at(previous).m_prevNode)
	{
		//previous->setTileID(4);
		path.push_back(previous->getPosition());
	}
	return path;
}