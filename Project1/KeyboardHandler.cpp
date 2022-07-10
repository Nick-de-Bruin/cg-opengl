#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler() { }
KeyboardHandler::~KeyboardHandler() { }

void KeyboardHandler::AddKey(char key, std::function<void()> fn)
{
	if (keyMap.count(key) == 0)
		keyMap.insert(std::make_pair(key, fn));
}

void KeyboardHandler::RemoveKey(char key)
{
	if (keyMap.count(key) > 0)
		keyMap.erase(key);
}

void KeyboardHandler::HandleInput(char key) 
{
	if (keyMap.find(key) != keyMap.end())
		keyMap.at(key)();
}
