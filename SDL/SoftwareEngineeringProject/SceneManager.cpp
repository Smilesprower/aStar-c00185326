#include "stdafx.h"
#include "SceneManager.h"

SceneManager * SceneManager::m_inst = nullptr;
SceneManager * SceneManager::Instance()
{
	if (!m_inst)
	{
		m_inst = new SceneManager();
	}
	return m_inst;
}

void SceneManager::onEvent(bool &quit)
{
	m_currentScene->onEvent(quit);
}

void SceneManager::update(float deltaTime)
{
	m_currentScene->update(deltaTime);
}

void SceneManager::changeScene(int scene)
{
	m_currentScene->stop();
	m_currentScene = m_scenes[scene];
	m_currentScene->start();
}

void SceneManager::render(SDL_Renderer* renderer)
{
	m_currentScene->render(renderer);
}

void SceneManager::addScene(Scene *scene)
{
	if (m_currentScene == nullptr) {
		m_currentScene = scene;
	}
	m_scenes.push_back(scene);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (std::vector<Scene*>::iterator i = m_scenes.begin(), e = m_scenes.end(); i != e; i++) 
	{
		delete *i;
	}
	delete m_inst;
	m_scenes.clear();
}