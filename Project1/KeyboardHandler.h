#pragma once

#include <functional>
#include <map>

class KeyboardHandler
{
private:
	std::map<char, std::function<void(float)>> keyMap;

public:
	KeyboardHandler();
	~KeyboardHandler();
	void AddKey(char key, std::function<void(float)> fn);
	void RemoveAll();
	void RemoveKey(char key);
	void HandleInput(char key, float t);
};

