#include "stdafx.h"
#include "Keyboard.h"

Keyboard * Keyboard::m_inst = nullptr;
Keyboard::Keyboard()
{
	currentKey = SDL_GetKeyboardState(&length);
	previousKey = new Uint8[length];
}


Keyboard::~Keyboard()
{
	delete[] previousKey;
	previousKey = nullptr;
}

Keyboard * Keyboard::Instance()
{
	if (!m_inst)
	{
		m_inst = new Keyboard();
	}
	return m_inst;
}

void Keyboard::update()
{
	std::memcpy(previousKey, currentKey, length);
	currentKey = SDL_GetKeyboardState(NULL);
}

bool Keyboard::keyDown(int key)
{
	return currentKey[key];
}

bool Keyboard::keyPressed(int key)
{
	return (currentKey[key] && !previousKey[key]);
}

bool Keyboard::keyReleased(int key)
{
	return (!currentKey[key] && previousKey[key]);
}

