#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene(SDL_Renderer* renderer);
	~MenuScene();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void onEvent(bool &quit) override;
	void start()override;
	void stop()override;
	void loadContent(SDL_Renderer* renderer);

private:

	bool m_changeColor;

};
