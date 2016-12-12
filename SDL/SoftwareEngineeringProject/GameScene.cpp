#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer, int width, int height)
	: m_renderState(Intro)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_camera{ 0, 0, m_screenWidth, m_screenHeight }
	, m_dest{ 312, 250, 175, 100 }						// Location of the title screen co - ords
	, m_source{ 0, 40, 175, 100 }						// Source Rect for the title screen image in texture
	, m_sourceRect{ 0, 0, NODE_SIZE, NODE_SIZE }		// Source Rect for tiles and player
	, m_astar(MAX_NODES, MAX_NODES_PER_AXIS)			
	, m_numOfActiveEnemies(0)
	, m_wallOffset(0)
	, m_player(SDL_Point{ 0,0 }, NODE_SIZE)
	, m_threadPool(new ThreadPool())
	, m_preCalcPaths(MAX_NUM_OF_WALLS)
	, m_numOfEnemiesFinished(0)
	, m_cameraState(Default)
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
	m_neighbourTiles = m_astar.getNeighbours();
	for (int i = 0; i < MAX_ENEMIES; i++)
		m_enemies.push_back(new Enemy(NODE_SIZE));
	loadContent(renderer);
}

GameScene::~GameScene()
{
	for (int i = 0; i < MAX_NODES; i++)
	{
		delete m_nodes[i];
		m_nodes[i] =  nullptr;
	}
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		delete m_enemies[i];
		m_enemies[i] = nullptr;
	}
	SDL_DestroyMutex(m_lock);
	delete m_threadPool;
}

void GameScene::render(SDL_Renderer* renderer)
{
	// Intro State
	////////////////////////////
	if (m_renderState == Intro)
		SDL_RenderCopy(renderer, m_texture, &m_source, &m_dest);
	
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

			SDL_RenderCopy(renderer, m_texture, &m_sourceRect, &m_nodes[currentNode]->getRect(m_camera));
			xCounter++;
		}
		// DRAWING PLAYER
		///////////////////////////////////////////////////////
		SDL_Point temp = m_player.getTileID();
		m_sourceRect.x = temp.x * NODE_SIZE;
		m_sourceRect.y = temp.y * NODE_SIZE;
		SDL_RenderCopy(renderer, m_texture, &m_sourceRect, &m_player.getRect(m_camera));

		// DRAWING ENEMIES
		///////////////////////////////////////////////////////
		for (int i = 0; i < m_numOfActiveEnemies; i++)
		{
			if (m_enemies[i]->getActive())
			{
				SDL_Point temp = m_enemies[i]->getTileID();
				m_sourceRect.x = temp.x * NODE_SIZE;
				m_sourceRect.y = temp.y * NODE_SIZE;
				SDL_RenderCopy(renderer, m_texture, &m_sourceRect, &m_enemies[i]->getRect(m_camera));
			}
		}
	}
}

void GameScene::update(float deltaTime)
{
	if (m_updateState == Run)
	{
		// ENEMY UPDATE
		///////////////////////////////////////////////////////
		for (int i = 0; i < m_numOfActiveEnemies; i++)
		{
			if (m_enemies[i]->getActive())
			{
				int enemyTile = m_enemies[i]->getTile();	// Index of tile the enemy is on
				int playerTile = m_player.getTile();		// Index of tile player is on
				int state = m_enemies[i]->getState();		// Current state of the enemy

				if (state == GetPath)
				{
					m_threadPool->addTask(std::bind(&GameScene::getPath, this, i, m_wayPoints[m_wayPoints.size() - 1], enemyTile, true));
					m_enemies[i]->setState(AwaitingPreCalcPaths);
				}
				else if (state == AwaitingPreCalcPaths)
				{
					if (m_enemies[i]->getPathCount() > 0)
					{
						for (int j = m_wayPoints.size() - 1; j >= 0; j--)
						{
							m_enemies[i]->addPath(m_preCalcPaths[j]);
						}
						m_enemies[i]->setState(Update);
					}
				}
				else if (state == Update)
				{
					m_enemies[i]->update(deltaTime, &m_nodes, m_neighbourTiles);
				}
				else if (state == Finished)
				{
					if (enemyTile == playerTile)
					{
						m_nodes.at(enemyTile)->setOccupied(false);
						m_enemies[i]->setActive(false);
						m_numOfEnemiesFinished++;
					}
					else
					{
						m_enemies[i]->setCollision(false);
						m_threadPool->addTask(std::bind(&GameScene::getPath, this, i, playerTile, enemyTile, true));
					}
				}
			}
		}
		if (m_numOfEnemiesFinished == m_numOfActiveEnemies)
		{
			reset();
		}
		// CAMERA STATES
		///////////////////////////////////////////////////////
		if (m_cameraState == EnemyCam)
		{
			SDL_Point temp = m_enemies[0]->getPosition();
			m_camera.x = temp.x - HALF_SCREEN_WIDTH;
			m_camera.y = temp.y - HALF_SCREEN_HEIGHT;
		}
		else if (m_cameraState == PlayerCam)
		{
			SDL_Point temp = m_player.getPosition();
			m_camera.x = temp.x - HALF_SCREEN_WIDTH;
			m_camera.y = temp.y - HALF_SCREEN_HEIGHT;
		}
		checkCameraBounds();
		m_player.update(deltaTime, &m_nodes, m_worldHeight);
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
			// Max Nodes, Nodes Per Axis, Wall Offset, Wall Number, Active Enemies, Enemy Start Pos, fit on one row
			setUpWorld(1200, 40, 10, 3, 5, false);
			m_renderState = Run;
		}
		else if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_2))
		{
			// Max Nodes, Nodes Per Axis, Wall Offset, Wall Number, Active Enemies, Enemy Start Pos, fit on one row
			setUpWorld(10000, 100, 16, 6, 50, true);
			m_renderState = Run;
		} 
		else if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_3))
		{
			// Max Nodes, Nodes Per Axis, Wall Offset, Wall Number, Active Enemies, Enemy Start Pos, fit on one row
			setUpWorld(MAX_NODES, MAX_NODES_PER_AXIS, 55, MAX_NUM_OF_WALLS, MAX_ENEMIES, true);
			m_renderState = Run;
		}
		break;
	case Run:
		if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_RETURN) && m_renderState == Run && m_updateState != Run)
			m_updateState = Run;
		if (Keyboard::Instance()->keyDown(SDL_SCANCODE_LEFT) && m_cameraState == Default)
			m_camera.x -= NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_RIGHT) && m_cameraState == Default)
			m_camera.x += NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_UP) && m_cameraState == Default)
			m_camera.y -= NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_DOWN) && m_cameraState == Default)
			m_camera.y += NODE_SIZE;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_Q))
			m_cameraState = Default;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_W))
			m_cameraState = EnemyCam;
		else if (Keyboard::Instance()->keyDown(SDL_SCANCODE_E))
			m_cameraState = PlayerCam;
		break;
	}
}
void GameScene::loadContent(SDL_Renderer * renderer)
{			
	// Load Stuff here
	if (TextureManager::Instance()->load("assets/tiles.png", Textures::Tiles, renderer))
		m_texture = TextureManager::Instance()->getTexture(Textures::Tiles);
}
// SETUP UP GAMEWORLD
///////////////////////////////////////////////////////
void GameScene::setUpWorld(int non, int npa, int wallOffset, int numOfWalls, int nae, bool fitOnOneRow)
{
	srand(SDL_GetTicks());// Seed Random Based on current gametick
	int randomStartPos = rand() % ((wallOffset) - (wallOffset/2 )+ 1) + (wallOffset / 2);
	m_wallOffset = randomStartPos;
	m_numOfActiveEnemies = nae;
	std::vector<int> gapInWallIndex;

	int row = 0;												// Counter for number of nodes per row
	int col = 0;												// Counter for number of cols
	int wallCount = 0;											// Counts the number of walls
	int endPoint = ((non / npa) - 1) * MAX_NODES_PER_AXIS;		// The end Y point position
	int count = 0;												// Var to make every second wall not walkable		
	int dist = 0;												// Dist from last wall tile to end of map


	// SETUP ALL NODES/TILES
	///////////////////////////////////////////////////////
	for (int i = 0; i < non; i++)
	{
		if (row > m_wallOffset && wallCount < numOfWalls -1)
		{
			m_wallOffset += wallOffset;
			wallCount++;
		}

		// SETUP WALLS, DYNAMIC FOR ANY VALUE
		///////////////////////////////////////////////////////
		if ((row % m_wallOffset == 0) && row > 0 && (col > 0 && col < endPoint))			
		{
			m_nodes[row + col]->setUp(false);
		}
		else if (row % m_wallOffset == 0 && row > 0 && (col == 0 || col == endPoint))
		{
			if (i > npa && 2 % count != 0)
				count = 1;

			count += 1;
			if (count % 2 == 1)
			{
				m_nodes[row + col]->setUp(true);
				gapInWallIndex.push_back(row + col);
			}
			else
				m_nodes[row + col]->setUp(false);
		}
		else
		{
			m_nodes[row + col]->setUp(true);
		}
		row++;
		if (row == npa)
		{
			row = 0;
			col += MAX_NODES_PER_AXIS;
			dist = m_wallOffset + 1;
			m_wallOffset = randomStartPos;
			wallCount = 0;
		}
	}
	m_worldWidth = npa * NODE_SIZE;
	m_worldHeight = (non / npa) * NODE_SIZE;
	m_player.reset(SDL_Point{ 1, 20 });

	// SPAWNS ENEMIES BASED ON SPACE LEFT IN COLUMNS, INCREASES ROW IF NOT ENOUGH SPACE.
	// IF THE GAP IS AT THE TOP THE ENEMIES Y VALUE WILL BE AT THE BOTTOM TO ENSURE THE FURTHEST DISTANCE
	///////////////////////////////////////////////////////
	SDL_Point enemyStartPos = SDL_Point{ dist, 0 };
	if (count % 2 == 0)
		enemyStartPos.y = m_worldHeight / NODE_SIZE - 1;
	else
		enemyStartPos.y = nae / (npa - dist);
	if (fitOnOneRow)
	{
		for (int i = 0; i < m_numOfActiveEnemies; i++)
		{
			m_enemies[i]->setUp(enemyStartPos, 0);
			enemyStartPos.x++;
			if (enemyStartPos.x > npa - 1)
			{
				enemyStartPos.x = dist;
				enemyStartPos.y--;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_numOfActiveEnemies; i++)
		{
			m_enemies[i]->setUp(enemyStartPos, 1);
			enemyStartPos.x++;
		}
	}
	// SORTS THE GAPINTHEWALL INDEXS TO MAKE CALCULATING PATHS EASIER GAP1 - GAP2 - GAP3 ETC
	///////////////////////////////////////////////////////
	int offset = 0;
	int tempSize = gapInWallIndex.size() / 2;
	if (gapInWallIndex.size() % 2 != 0)
		offset = 1;
	for (int i = 0; i < tempSize; i++)	// Reorders the waypoints correctly in the vector 
	{
		m_wayPoints.push_back(gapInWallIndex[i]);
		m_wayPoints.push_back(gapInWallIndex[i + tempSize + offset]);
	}
	if(gapInWallIndex.size() % 2 != 0)	// For odd number of walls push back last
		m_wayPoints.push_back(gapInWallIndex[tempSize]);

	// THREADING WAYPOINTS
	///////////////////////////////////////////////////////
	for (int i = 0; i < m_wayPoints.size()-1; i++)
		m_threadPool->addTask(std::bind(&GameScene::getPath, this, i, m_wayPoints[i], m_wayPoints[i+1], false));
}
// RESET VARS
///////////////////////////////////////////////////////
void GameScene::reset()
{
	for (int i = 0; i < MAX_NUM_OF_WALLS; i++)
		m_preCalcPaths[i].clear();
	m_renderState = Intro;
	m_updateState = Stopped;
	m_numOfActiveEnemies = 0;
	m_numOfEnemiesFinished = 0;
	m_wayPoints.clear();
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
// THREADPOOL FUNCTIONS
///////////////////////////////////////////////////////
void GameScene::getPath(int index, int start, int end, bool enemy)
{
	std::vector<SDL_Point> temp = m_astar.findPath(&m_nodes, start, end);
	SDL_LockMutex(m_lock);
	if (!enemy)
		m_preCalcPaths[index] = temp;
	else
		m_enemies[index]->SetPath(temp);
	SDL_UnlockMutex(m_lock);
}

void GameScene::start()
{
}
void GameScene::stop()
{
}