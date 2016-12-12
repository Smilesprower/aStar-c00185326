#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include "ResourceIdentifier.h"
#include "Keyboard.h"
#include "Debug.h"

class SceneManager;

class Scene
{
public:
	virtual ~Scene(){};
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void onEvent(bool &quit) = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
};

#include "SceneManager.h"

