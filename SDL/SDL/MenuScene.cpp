#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene(SDL_Renderer* renderer)
{
	loadContent(renderer);
}

MenuScene::~MenuScene()
{
}

void MenuScene::render(SDL_Renderer* renderer)
{

	TextureManager::Instance()->drawMessage(Textures::Text1, 200, 100, 400, 50, renderer);
	//if (!m_changeColor)
	//	TextureManager::Instance()->draw(Textures::Player, 100, 100, 100, 100, renderer);
	//else
	//	TextureManager::Instance()->draw(Textures::Player, 100, 100, 200, 200, renderer);
}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::onEvent(bool &quit)
{
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_ESCAPE))
		quit = true;
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_A))
		SceneManager::Instance()->changeScene(Scenes::GameScene);
}
void MenuScene::start()
{
	std::cout << "Menu Scene Stated" << std::endl;
}
void MenuScene::stop()
{
	std::cout << "Menu Scene Stopped" << std::endl;
}

void MenuScene::loadContent(SDL_Renderer * renderer)
{
	if (!TextureManager::Instance()->loadFont("Press one of the following to start", Textures::Text1, renderer))
		DEBUG_MSG("Texture Query Failed");

	//// For the moment this will load all Textures;
	//if (!TextureManager::Instance()->load("assets/1.png", Textures::Player, renderer))
	//	DEBUG_MSG("Texture Query Failed");
	//if (!TextureManager::Instance()->load("assets/2.png", Textures::Level, renderer))
	//	DEBUG_MSG("Texture Query Failed");
}


