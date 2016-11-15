#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer)
	: m_nodes(std::vector<Node*>(0))
	, m_state(Intro)
{

	for (int i = 0; i < 1000; i++)
	{
		m_nodes.push_back(new Node());
	}
	loadContent(renderer);
}

GameScene::~GameScene()
{
	for (int i = 0; i < m_numOfNodes; i++)
	{
		delete m_nodes[i];
		m_nodes[i] =  nullptr;
	}
}

void GameScene::render(SDL_Renderer* renderer)
{
	int count = 0;
	// Intro State
	////////////////////////////
	if (m_state == Intro)
	{
		TextureManager::Instance()->drawMessage(Textures::Text1, 200, 100, 400, 50, renderer);
	}
	// Run State
	////////////////////////////
	else if (m_state == Run)
	{
		for (int i = 0; i < m_numOfNodes; i++)
		{
				SDL_Color col = m_nodes.at(i)->getColor();
				SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
				SDL_RenderFillRect(renderer, &m_nodes.at(i)->getRect());
				count++;
		}

		SDL_Color col = m_enemy.getColor();
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawRect(renderer, &m_enemy.getRect());
	}
}

void GameScene::update(float deltaTime)
{
	std::cout << m_start << std::endl;
	if (m_start)
	{
		// Goal Node, Enemy Start Node
		m_enemy.SetPath(astar.findPath(m_nodes, 0, m_enemy.getStartNode()));
		m_start = false;
	}
	if (!m_enemy.isFinished())
		m_enemy.update(deltaTime);
	else
		reset();
}

void GameScene::onEvent(bool &quit)
{
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_ESCAPE))
		quit = true;
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_A) && m_state == Intro)
	{
		setUp(100, 10, 50);
		m_state = Run;
	}
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_RETURN) && m_state == Run)
	{
		m_start = true;
	}
}
void GameScene::start()
{
}
void GameScene::stop()
{
}

void GameScene::loadContent(SDL_Renderer * renderer)
{
	// Load Stuff here
	////////////////////////////
	if (!TextureManager::Instance()->loadFont("Press one of the following to start", Textures::Text1, renderer))
		DEBUG_MSG("Texture Query Failed");
}
// Set up variables
////////////////////////////
void GameScene::setUp(int non, int npa, int ns) // Num of Nodes, Nodes per Axis, Node Size
{
	std::cout << "Setting Up" << std::endl;
	m_start = false;
	m_numOfNodes = non;
	m_nodesPerAxis = npa;
	m_nodeSize = ns;
	m_x = 0;
	m_y = 0;


	for (int i = 0; i < m_numOfNodes; i++)
	{
		if (i % (2 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis
			|| i % (4 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis
			|| i % (6 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis)
		{
			m_nodes[i]->setUp(m_x, m_y, m_nodeSize, i, false);
		}
		else
		{
			m_nodes[i]->setUp(m_x, m_y, m_nodeSize, i, true);
		}
		m_x++;
		if (m_x >= m_nodesPerAxis)
		{
			m_x = 0;
			m_y++;
		}
	}
	astar.setUp(m_numOfNodes, m_nodesPerAxis, m_nodeSize);
	m_enemy.setUp(SDL_Point{ 8, 9 }, m_nodesPerAxis, m_nodeSize);
	std::cout << "Done" << std::endl;
}
// Reset up variables
////////////////////////////
void GameScene::reset()
{
	for (int i = 0; i < m_numOfNodes; i++)
		m_nodes.at(i)->setUsing(false);

	m_enemy.reset();
	m_state = Intro;
	m_start = false;
	m_numOfNodes = 0;
	m_nodesPerAxis = 0;
	m_nodeSize = 0;
	m_x = 0;
	m_y = 0;
}

