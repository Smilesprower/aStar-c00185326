#pragma once
#include <iostream>
#include "Scene.h"
#include "Enemy.h"
#include "Player.h"
#include "AStar.h"
#include "Node.h"
#include "ThreadPool.h"
#include "Logger.h"

class GameScene : public Scene
{

public:
	enum autoRunState
	{
		Small,
		Medium,
		Large
	};
	enum EnemyState
	{
		GetPath,
		AwaitingPreCalcPaths,
		Update,
		Finished
	};
	enum CameraState
	{
		Default,
		PlayerCam,
		EnemyCam
	};
	enum State
	{
		Intro,
		Run,
		End,
		Waiting,
		Stopped,
	};

	GameScene(SDL_Renderer* renderer, int width, int height);
	~GameScene();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void onEvent(bool &quit) override;
	void start()override;
	void stop()override;
	void loadContent(SDL_Renderer* renderer);
	void setUpWorld(int numOfNodes, int nodesPerAxis, int wallOffset, int numOfWalls, int numActiveEnemies, bool fitOnOneRow);
	void reset();
	void checkCameraBounds();
	void getPath(int index, int start, int end, bool enemy);
private:
	const int MAX_AUTO_RUNS = 3;
	const int MAX_NUM_OF_WALLS = 18;
	const int MAX_NODES = 1000000;
	const int MAX_NODES_PER_AXIS = 1000;
	const int NODE_SIZE = 20;
	const int MAX_NUM_PER_ROW = 40;
	const int MAX_NUM_PER_COLUMN = 30;
	const int MAX_NUM_OF_DRAWABLE_NODES = 1200;	// row * col
	const int MAX_ENEMIES = 500;
	const int HALF_SCREEN_WIDTH = 400;
	const int HALF_SCREEN_HEIGHT = 300;

	int m_renderState, m_updateState;
	int m_screenWidth, m_screenHeight, m_worldWidth, m_worldHeight;
	int m_numOfActiveEnemies, m_wallOffset, m_numOfEnemiesFinished;
	int m_cameraState;
	Player m_player;
	AStar m_astar;
	std::vector<Node*> m_nodes;
	std::vector<Enemy*> m_enemies;
	std::vector<std::vector<SDL_Point>> m_preCalcPaths;
	std::vector<int> m_wayPoints;
	SDL_Texture* m_texture;
	SDL_Rect m_source, m_dest, m_camera, m_sourceRect;
	ThreadPool *m_threadPool;
	SDL_mutex * m_lock;
	int *m_neighbourTiles;
	bool m_autoRun, m_startGame, m_threadsEnabled, m_writeToFile;
	int m_pathCount;
	int m_startTime, m_endTime, m_totalTasks, m_numOfCompletedPaths, m_autoRunState, m_numOfAutoRuns;
};
