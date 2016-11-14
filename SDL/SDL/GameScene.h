
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

	GameScene(SDL_Renderer* renderer);
	~GameScene();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void onEvent(bool &quit) override;
	void start()override;
	void stop()override;
	void loadContent(SDL_Renderer* renderer);
	void setUp(int non, int npa, int ns);
	void reset();


private:
	int m_state;
	bool m_start;
	int m_numOfNodes;
	int m_nodesPerAxis;
	int m_nodeSize;
	int m_x;
	int m_y;

	Enemy m_enemy;

	AStar astar;

	std::vector<Node*> m_nodes;
	//std::vector<Node> *m_nodes;
	std::vector<SDL_Point> m_path;
};
