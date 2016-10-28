#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene(SDL_Renderer* renderer)
	: m_changeColor(false)
{
	loadContent(renderer);
}

MenuScene::~MenuScene()
{
}

void MenuScene::render(SDL_Renderer* renderer)
{
	if (!m_changeColor)
		TextureManager::Instance()->draw(Textures::Player, 100, 100, 100, 100, renderer);
	else
		TextureManager::Instance()->draw(Textures::Player, 100, 100, 200, 200, renderer);
}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::onEvent(bool &quit)
{
	if (Keyboard::Instance()->keyPressed(SDL_SCANCODE_ESCAPE))
		quit = true;
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_A))
		m_changeColor = false;
	if (Keyboard::Instance()->keyReleased(SDL_SCANCODE_S))
		m_changeColor = true;
}
void MenuScene::start()
{

}
void MenuScene::stop()
{
}

void MenuScene::loadContent(SDL_Renderer * renderer)
{
	// For the moment this will load all Textures;
	if (!TextureManager::Instance()->load("assets/1.png", Textures::Player, renderer))
		DEBUG_MSG("Texture Query Failed");
	if (!TextureManager::Instance()->load("assets/2.png", Textures::Level, renderer))
		DEBUG_MSG("Texture Query Failed");
}


