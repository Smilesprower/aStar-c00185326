#include "stdafx.h"
#include "AStar.h"

const int NEIGHBOUR_COUNT = 4;
const int COST = 5;


AStar::AStar()
{
}

AStar::AStar(int numOfNodes, int numOfNodesPerAxis, int nodeSize)
	: m_numOfNodes(numOfNodes)
	, m_numOfNodesPerAxis(numOfNodesPerAxis)
	, m_nodeDimensions(nodeSize)
{
	m_neighbourNode[0] = 1; // Right
	m_neighbourNode[1] = -1; // Left
	m_neighbourNode[2] = numOfNodesPerAxis; // Down
	m_neighbourNode[3] = -numOfNodesPerAxis; // Up
}

AStar::~AStar()
{
}

std::vector<SDL_Point> AStar::findPath(std::vector<Node*> m_nodes, int startIndex, int goalIndex)
{
	Node* start = m_nodes.at(startIndex);
	Node* goal = m_nodes.at(goalIndex);

	if (start != 0 && goal != 0)
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, NodeSearchCostComparer> openset;
		start->setGcost(0);
		start->setFcost(getHeuristic(start, goal));
		start->setOpen(true);
		openset.push(std::pair<int, int>(start->getFcost(), startIndex));

		int previousCost = 0;

		while (openset.size() != 0)
		{
			Node* current = m_nodes.at(openset.top().second);
			openset.pop();
			if (current == goal)
			{
				return createPath(goal, start);
			}
			current->setOpen(false); 
			current->setClose(true); 

			for (int i = 0; i < NEIGHBOUR_COUNT; i++)
			{
				int neighbourIndex = getNeighbourIndex(current, i);

				Node* neighbour;
				if (neighbourIndex == -1){ neighbour = 0; }
				else { neighbour = m_nodes.at(neighbourIndex); }

				if (neighbour == 0 || neighbour->close()
					|| neighbour == current->getPrevious()
					|| neighbour->walkable() == false)
				{
					continue;
				}
				int tenativeGCost = current->getCcost() + COST;
				if (tenativeGCost <= neighbour->getCcost())
				{
					neighbour->setPrevious(current);
					neighbour->setGcost(tenativeGCost);
					neighbour->setFcost(neighbour->getCcost() + getHeuristic(neighbour, goal));
				}

				if (neighbour->open() == false)
				{
					neighbour->setOpen(true);
					openset.push(std::pair<int, int>(neighbour->getFcost(), neighbourIndex));
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

std::vector<SDL_Point> AStar::createPath(Node * goalNode, Node * startNode)
{
	std::vector<SDL_Point> path;
	for (Node* previous = goalNode; previous->getPrevious() != 0; previous = previous->getPrevious())
	{
		path.push_back(previous->getPosition());
	}
	path.push_back(startNode->getPosition());
	return path;
}
