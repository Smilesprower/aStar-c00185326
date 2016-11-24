#pragma once
#include "SDL.h"
#include <iostream>

class Keyboard
{
public:
	static Keyboard * Instance();
	void update();

	//True if a key is pressed
	int keyDown(int key);
	//True if the key was pressed this frame
	int keyPressed(int key);
	//True if the key was released this frame
	int keyReleased(int key);

private:
	int length;
	//State of keyboard last frame
	Uint8* previousKey;
	//State of keyboard this frame
	const Uint8* currentKey;

	static Keyboard *m_inst;
	Keyboard();
	~Keyboard();
};



