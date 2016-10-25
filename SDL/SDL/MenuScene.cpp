#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::render(SDL_Renderer* renderer)
{
	TextureManager::Instance()->draw(Textures::Player, 100, 100, 100, 100, renderer);
}

void MenuScene::update(float deltaTime)
{
}

void MenuScene::onEvent()
{
}
void MenuScene::start()
{
}
void MenuScene::stop()
{
}


