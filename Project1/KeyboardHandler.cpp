#include "KeyboardHandler.h"
#include <iostream>

KeyboardHandler::KeyboardHandler() { }
KeyboardHandler::~KeyboardHandler() { }

void KeyboardHandler::AddKey(char key, std::function<void(float)> fn)
{
	if (keyMap.count(key) == 0)
		keyMap.insert(std::make_pair(key, fn));
}

void KeyboardHandler::RemoveAll() {	keyMap.clear(); }

void KeyboardHandler::RemoveKey(char key)
{
	if (keyMap.count(key) > 0)
		keyMap.erase(key);
}

void KeyboardHandler::HandleInput(char key, float t) 
{
	if (keyMap.count(key) > 0)
		keyMap.at(key)(t * 5);
}
