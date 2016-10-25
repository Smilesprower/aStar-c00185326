#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void onEvent()override;
	void start()override;
	void stop()override;

private:
};
