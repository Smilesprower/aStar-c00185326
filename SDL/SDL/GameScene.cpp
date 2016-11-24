#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer, int width, int height)
	: m_state(Intro)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_camera{ 0, 0, m_screenWidth, m_screenHeight }
	, m_dest{ 312, 250, 175, 100}
	, m_source{ 0, 40, 175, 100}
	, m_sourceRect{ 0, 0, NODE_SIZE, NODE_SIZE }
	, m_astar(MAX_NODES, MAX_NODES_PER_AXIS, NODE_SIZE)
{

	for (int i = 0; i < MAX_NODES; i++)
	{
		m_nodes.push_back(new Node(i, m_x, m_y, NODE_SIZE));
		m_x++;
		if (m_x == MAX_NODES_PER_AXIS)
		{
			m_x = 0;
			m_y++;
		}
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
	// Intro State
	////////////////////////////
	if (m_state == Intro)
	{
		SDL_RenderCopyEx(renderer, m_texture, &m_source, &m_dest, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
	// Run State
	////////////////////////////
	else if (m_state == Run)
	{
		int startNodeX = 0;
		int startNodeY = 0;
		if(m_camera.x != 0)
			startNodeX = m_camera.x / NODE_SIZE;						
		if(m_camera.y != 0)
			startNodeY = m_camera.y / NODE_SIZE * MAX_NODES_PER_AXIS;	
		int lastNodeX = startNodeX + MAX_NUM_PER_ROW - 1;				// Last node in the X direction
		int xCounter = startNodeX;										// Holds the count for num of nodes in the X direction

		for (int i = 0; i < MAX_NUM_OF_DRAWABLE_NODES; i++)
		{
			if (xCounter > lastNodeX)
			{
				startNodeY += MAX_NODES_PER_AXIS;						// Because I use a 1D array we offset by the nodes Per Axis
				xCounter = startNodeX;									// Reset count for num of nodes in the X direction
			}
			int currentNode = xCounter + startNodeY;
			SDL_Point temp = m_nodes[currentNode]->getTileID();
			m_sourceRect.x = temp.x * NODE_SIZE;
			m_sourceRect.y = temp.y * NODE_SIZE;

			SDL_RenderCopyEx(renderer, m_texture, &m_sourceRect, &m_nodes[currentNode]->getRect(m_camera), 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			xCounter++;
		}

		SDL_Color col = m_enemy.getColor();
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
		SDL_RenderFillRect(renderer, &m_enemy.getRect(m_camera));
	}
}

void GameScene::update(float deltaTime)
{
	if (m_start)
	{
		//int x = SDL_GetTicks();
		m_enemy.SetPath(m_astar.findPath(m_nodes, 0, m_enemy.getStartNode()));
		//int y = SDL_GetTicks();
		//std::cout << y - x << std::endl;
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

	switch (m_state)
	{
	case Intro:
		if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_1))
		{
			setUp(1200, 40);
			m_state = Run;
		}
		else if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_3))
		{
			setUp(MAX_NODES, MAX_NODES_PER_AXIS);
			m_state = Run;
		}
		break;
	case Run:
		if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_RETURN) && !m_start)
			m_start = true;
		if (Keyboard::Instance()->keyDown(SDL_SCANCODE_LEFT))
			m_camera.x -= NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_RIGHT))
			m_camera.x += NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_UP))
			m_camera.y -= NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_DOWN))
			m_camera.y += NODE_SIZE;
		checkCameraBounds();
		break;
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
	if (TextureManager::Instance()->load("assets/tiles.png", Textures::Tiles, renderer))
		m_texture = TextureManager::Instance()->getTexture(Textures::Tiles);
}
// Set up variables
////////////////////////////
void GameScene::setUp(int non, int npa) // Num of Nodes, Nodes per Axis
{
	std::cout << "Setting Up" << std::endl;
	m_start = false;
	m_numOfNodes = non;
	m_nodesPerAxis = npa;
	m_x = 0; // Counter for number of nodes per row
	m_y = 0; // Counter for number of cols

	// Reset the nodes I need
	for (int i = 0; i < m_numOfNodes; i++)
	{
		m_nodes[m_x + m_y]->setUp(true);
		m_x++;
		if (m_x == m_nodesPerAxis)
		{
			m_x = 0;
			m_y += MAX_NODES_PER_AXIS;
		}
	}

	m_worldWidth = m_nodesPerAxis * NODE_SIZE;
	m_worldHeight = (m_numOfNodes / m_nodesPerAxis) * NODE_SIZE;

	m_enemy.setUp(SDL_Point{ 10, 10 }, MAX_NODES_PER_AXIS, NODE_SIZE);
	std::cout << "Done" << std::endl;
}
// Reset up variables
////////////////////////////
void GameScene::reset()
{
	m_enemy.reset();
	m_state = Intro;
	m_start = false;
	m_numOfNodes = 0;
	m_nodesPerAxis = 0;
}

void GameScene::checkCameraBounds()
{
	// Camera Bounds
	//////////////////////////////
	if (m_camera.x < 0)
		m_camera.x = 0;
	else if (m_camera.x > m_worldWidth - m_camera.w)
		m_camera.x = m_worldWidth - m_camera.w;
	if (m_camera.y < 0)
		m_camera.y = 0;
	else if (m_camera.y > m_worldHeight - m_camera.h)
		m_camera.y = m_worldHeight - m_camera.h;
}

