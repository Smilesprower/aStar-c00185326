#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer, int width, int height)
	: m_renderState(Intro)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_camera{ 0, 0, m_screenWidth, m_screenHeight }
	, m_dest{ 312, 250, 175, 100}
	, m_source{ 0, 40, 175, 100}
	, m_sourceRect{ 0, 0, NODE_SIZE, NODE_SIZE }
	, m_astar(MAX_NODES, MAX_NODES_PER_AXIS, NODE_SIZE)
	, m_numOfActiveEnemies(0)
	, m_numOfRuns(0)
	, m_player(SDL_Point{0,0}, NODE_SIZE)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < MAX_NODES; i++)
	{
		m_nodes.push_back(new Node(i, x, y, NODE_SIZE));
		x++;
		if (x == MAX_NODES_PER_AXIS)
		{
			x = 0;
			y++;
		}
	}
	for (int i = 0; i < MAX_ENEMIES; i++)
		m_enemies.push_back(new Enemy(NODE_SIZE));
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
	if (m_renderState == Intro)
		SDL_RenderCopyEx(renderer, m_texture, &m_source, &m_dest, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	// Run State
	////////////////////////////
	else if (m_renderState == Run)
	{
		// DRAWING NODES
		///////////////////////////////////////////////////////
		int startNodeX = 0;
		int startNodeY = 0;
		if(m_camera.x != 0)
			startNodeX = m_camera.x / NODE_SIZE;						
		if(m_camera.y != 0)
			startNodeY = m_camera.y / NODE_SIZE * MAX_NODES_PER_AXIS;	
		int lastNodeX = startNodeX + MAX_NUM_PER_ROW - 1;				// Last node in the X direction
		int xCounter = startNodeX;										// Holds the count for num of nodes in the X direction

		m_sourceRect.y = 0;
		for (int i = 0; i < MAX_NUM_OF_DRAWABLE_NODES; i++)
		{
			if (xCounter > lastNodeX)
			{
				startNodeY += MAX_NODES_PER_AXIS;						// Because I use a 1D array we offset by the nodes Per Axis
				xCounter = startNodeX;									// Reset count for num of nodes in the X direction
			}
			int currentNode = xCounter + startNodeY;
			int temp = m_nodes[currentNode]->getTileID();
			m_sourceRect.x = temp * NODE_SIZE;

			SDL_RenderCopyEx(renderer, m_texture, &m_sourceRect, &m_nodes[currentNode]->getRect(m_camera), 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			xCounter++;
		}
		// DRAWING PLAYER
		///////////////////////////////////////////////////////
		SDL_Point temp = m_player.getTileID();
		m_sourceRect.x = temp.x * NODE_SIZE;
		m_sourceRect.y = temp.y * NODE_SIZE;
		SDL_RenderCopyEx(renderer, m_texture, &m_sourceRect, &m_player.getRect(m_camera), 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);

		// DRAWING ENEMIES
		///////////////////////////////////////////////////////
		for (int i = 0; i < m_numOfActiveEnemies; i++)
		{
			SDL_Point temp = m_enemies[i]->getTileID();
			m_sourceRect.x = temp.x * NODE_SIZE;
			m_sourceRect.y = temp.y * NODE_SIZE;
			SDL_RenderCopyEx(renderer, m_texture, &m_sourceRect, &m_enemies[i]->getRect(m_camera), 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
		}
	}
}

void GameScene::update(float deltaTime)
{
	if (m_updateState == Waiting)
	{
		m_enemies[0]->SetPath(m_astar.findPath(&m_nodes, m_player.getTile(), m_enemies[0]->getStartNode(),0));
		m_updateState = Run;
	}
	else if (m_updateState == Run)
	{
		m_player.update(deltaTime);
		if (!m_enemies[0]->isFinished())
		{
			m_enemies[0]->update(deltaTime);
		}
		else if(m_enemies[0]->isFinished())
		{
			if (m_enemies[0]->getTile() == m_player.getTile())
			{
				reset();
			}
			else
			{
				int x = m_enemies[0]->getTile();
				quickSetUp();
				m_enemies[0]->resetPath();
				m_enemies[0]->SetPath(m_astar.findPath(&m_nodes, m_player.getTile(), m_enemies[0]->getTile(), 0));
			}
		}
	}

}

void GameScene::onEvent(bool &quit)
{
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_ESCAPE))
		quit = true;

	switch (m_renderState)
	{
	case Intro:
		if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_1))
		{
			m_wallStartPoint.push_back(10);
			m_wallStartPoint.push_back(20);
			m_wallStartPoint.push_back(30);
			setUpWorld(1200, 40, 1);
			m_renderState = Run;
		}
		else if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_3))
		{
			m_wallStartPoint.push_back(10);
			m_wallStartPoint.push_back(20);
			m_wallStartPoint.push_back(30);
			setUpWorld(MAX_NODES, MAX_NODES_PER_AXIS, 1);
			m_renderState = Run;
		}
		break;
	case Run:
		if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_RETURN) && m_renderState == Run && m_updateState != Run)
			m_updateState = Waiting;
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
	if (TextureManager::Instance()->load("assets/tiles.png", Textures::Tiles, renderer))
		m_texture = TextureManager::Instance()->getTexture(Textures::Tiles);
}
// Set up variables
////////////////////////////
void GameScene::quickSetUp()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < m_numOfNodes; i++)
	{
		m_nodes[x + y]->setUp(0);
		x++;
		if (x == m_nodesPerAxis)
		{
			x = 0;
			y += MAX_NODES_PER_AXIS;
		}
	}
}

void GameScene::setUpWorld(int non, int npa, int nae) // Num of Nodes, Nodes per Axis, Num of Enemies
{
	std::cout << "Setting Up" << std::endl;
	m_numOfNodes = non;
	m_nodesPerAxis = npa;
	m_numOfActiveEnemies = nae;
	int x = 0; // Counter for number of nodes per row
	int y = 0; // Counter for number of cols
	int wallCounter = 3;
	bool flag = false;

	int wallSize = m_smallWall.size();
	int endPoint = (non / npa -1) * MAX_NODES_PER_AXIS;
	for (int i = 0; i < m_numOfNodes; i++)
	{
		//TODO: Fix Walls
		if (x + y == m_smallWall[0] + y && y > 1)
			m_nodes[x + y]->setUp(false);
		else if (x + y == m_smallWall[1] + y && y < endPoint)
			m_nodes[x + y]->setUp(false);
		else if (x + y == m_smallWall[2] + y && y > 1)
			m_nodes[x + y]->setUp(false);
		else
			m_nodes[x + y]->setUp(true);

		x++;
		if (x == m_nodesPerAxis)
		{
			x = 0;
			y += MAX_NODES_PER_AXIS;
		}
	}

	m_worldWidth = m_nodesPerAxis * NODE_SIZE;
	m_worldHeight = (m_numOfNodes / m_nodesPerAxis) * NODE_SIZE;

	m_player.reset(SDL_Point{ 2, 10 });

	// TODO: Set up all enemies
	for (int i = 0; i < m_numOfActiveEnemies; i++)
		m_enemies[i]->setUp(SDL_Point{ 35+i, 29 }, MAX_NODES_PER_AXIS);
	std::cout << "Done" << std::endl;
}
// RESET VARS
///////////////////////////////////////////////////////
void GameScene::reset()
{
	for (int i = 0; i < m_numOfActiveEnemies; i++)
		m_enemies[i]->reset();
	m_renderState = Intro;
	m_updateState = Stopped;
	m_numOfNodes = 0;
	m_nodesPerAxis = 0;
	m_numOfActiveEnemies = 0;
}
// CAMERA BOUNDARY CHECK
///////////////////////////////////////////////////////
void GameScene::checkCameraBounds()
{
	if (m_camera.x < 0)
		m_camera.x = 0;
	else if (m_camera.x > m_worldWidth - m_camera.w)
		m_camera.x = m_worldWidth - m_camera.w;
	if (m_camera.y < 0)
		m_camera.y = 0;
	else if (m_camera.y > m_worldHeight - m_camera.h)
		m_camera.y = m_worldHeight - m_camera.h;
}

