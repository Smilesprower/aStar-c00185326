
#pragma once
#include "Scene.h"
#include "Enemy.h"
#include "AStar.h"
#include "Node.h"

class GameScene : public Scene
{
public:
	enum State
	{
		Intro,
		Run,
		End
	};

	GameScene(SDL_Renderer* renderer, int width, int height);
	~GameScene();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void onEvent(bool &quit) override;
	void start()override;
	void stop()override;
	void loadContent(SDL_Renderer* renderer);
	void setUp(int non, int npa, int nae);
	void reset();
	void checkCameraBounds();


private:
	const int MAX_NODES = 1000000;
	const int MAX_NODES_PER_AXIS = 1000;
	const int NODE_SIZE = 20;
	const int MAX_NUM_PER_ROW = 40;
	const int MAX_NUM_PER_COLUMN = 30;
	const int MAX_NUM_OF_DRAWABLE_NODES = 1200;	// row * col
	const int MAX_ENEMIES = 500;

	int m_state;
	int m_screenWidth, m_screenHeight, m_worldWidth, m_worldHeight;
	bool m_start;
	int m_numOfNodes, m_nodesPerAxis, m_numOfActiveEnemies;
	int m_x, m_y;

	Enemy m_enemy;
	AStar m_astar;
	std::vector<Node*> m_nodes;
	std::vector<Enemy*> m_enemies;
	std::vector<int> m_wallStartPoint;
	std::vector<SDL_Point> m_path;
	SDL_Texture* m_texture;
	SDL_Rect m_source, m_dest, m_camera, m_sourceRect;
	
};
