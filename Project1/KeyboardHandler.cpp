#include "KeyboardHandler.h"
#include <iostream>

KeyboardHandler::KeyboardHandler() { }
KeyboardHandler::~KeyboardHandler() { }

void KeyboardHandler::AddKey(char key, std::function<void(float)> fn)
{
	if (keyMap.count(key) == 0)
		keyMap.insert(std::make_pair(key, fn));
}

void KeyboardHandler::RemoveKey(char key)
{
	if (keyMap.count(key) > 0)
		keyMap.erase(key);
}

void KeyboardHandler::HandleInput(char key, float t) 
{
	if (keyMap.find(key) != keyMap.end())
		keyMap.at(key)(t * 2.5);
}
