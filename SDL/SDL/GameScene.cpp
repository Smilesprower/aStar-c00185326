#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer)
	: m_nodes(new std::vector<Node>())
	, m_state(Intro)
{
	loadContent(renderer);
}

GameScene::~GameScene()
{
}

void GameScene::render(SDL_Renderer* renderer)
{
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
			SDL_Color col = m_nodes->at(i).getColor();
			SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
			SDL_RenderFillRect(renderer, &m_nodes->at(i).getRect());
		}

		SDL_Color col = m_enemy.getColor();
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawRect(renderer, &m_enemy.getRect());
	}
}

void GameScene::update(float deltaTime)
{
	if (m_start)
	{
		// Goal Node, Enemy Start Node
		m_enemy.SetPath(astar.findPath(m_nodes, 0, m_enemy.getStartNode()));
		m_start = false;
	}
	m_enemy.update(deltaTime);
}

void GameScene::onEvent(bool &quit)
{
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_ESCAPE))
		quit = true;
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_A) && m_state == Intro)
	{
		setUp(100, 10, 50);
		m_state = Run;
	}
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_RETURN) && m_state == Run)
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
void GameScene::setUp(int non, int npa, int ns)
{
	std::cout << "Setting Up" << std::endl;
	m_start = false;
	m_numOfNodes = non;
	m_nodesPerAxis = npa;
	m_nodeSize = ns;
	m_x = 0;
	m_y = 0;

	astar.setUp(m_numOfNodes, m_nodesPerAxis, m_nodeSize);
	m_enemy.setUp(SDL_Point{8, 9}, m_nodesPerAxis, m_nodeSize);

	for (int i = 0; i < m_numOfNodes; i++)
	{
		if (i % (2 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis
			|| i % (4 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis
			|| i % (6 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis
			|| i % (8 + (m_y * m_nodesPerAxis)) == 0 && i > m_nodesPerAxis && i < m_numOfNodes - m_nodesPerAxis)
		{
			Node temp(m_x, m_y, m_nodeSize, i, false);
			m_nodes->push_back(temp);
		}
		else
		{
			Node temp(m_x, m_y, m_nodeSize, i, true);
			m_nodes->push_back(temp);
		}
		m_x++;
		if (m_x >= m_nodesPerAxis)
		{
			m_x = 0;
			m_y++;
		}
	}
	std::cout << "Done" << std::endl;
}
// Reset up variables
////////////////////////////
void GameScene::reset()
{
	m_state = Intro;
	m_nodes->clear();
	m_start = false;
	m_numOfNodes = 0;
	m_nodesPerAxis = 0;
	m_nodeSize = 0;
	m_x = 0;
	m_y = 0;
}

