
#pragma once
#include "Scene.h"
#include "Enemy.h"
#include "Player.h"
#include "AStar.h"
#include "Node.h"

class GameScene : public Scene
{
public:
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
	void setUpWorld(int non, int npa, int nae, int offset);
	void quickSetUp();
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

	int m_renderState, m_updateState;
	int m_screenWidth, m_screenHeight, m_worldWidth, m_worldHeight;
	int m_numOfNodes, m_nodesPerAxis, m_numOfActiveEnemies, m_wallOffset;
	int m_numOfRuns;

	Player m_player;
	AStar m_astar;
	std::vector<Node*> m_nodes;
	std::vector<Enemy*> m_enemies;
	SDL_Texture* m_texture;
	SDL_Rect m_source, m_dest, m_camera, m_sourceRect;

};
