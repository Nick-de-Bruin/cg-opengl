#pragma once

#include <functional>
#include <map>

class KeyboardHandler
{
private:
	std::map<char, std::function<void()>> keyMap;

public:
	KeyboardHandler();
	~KeyboardHandler();
	void AddKey(char key, std::function<void()> fn);
	void RemoveKey(char key);
	void HandleInput(char key);
};

