#pragma once
#include "Scene.h"
#include <vector>

class SceneManager 
{
public:
	static SceneManager * Instance();
	void onEvent();
	void update(float deltaTime);
	void changeScene(int scene);
	void render(SDL_Renderer* renderer);
	void addScene(Scene *scene);

private:
	std::vector<Scene*>m_scenes;
	Scene *m_currentScene;
	static SceneManager *m_inst;
	SceneManager();
	~SceneManager();
};
