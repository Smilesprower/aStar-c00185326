#pragma once
#include "SDL.h"
#include <iostream>

class Keyboard
{
public:
	static Keyboard * Instance();
	void update();

	//True if a key is pressed
	bool keyDown(int key);
	//True if the key was pressed this frame
	bool keyPressed(int key);
	//True if the key was released this frame
	bool keyReleased(int key);

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



