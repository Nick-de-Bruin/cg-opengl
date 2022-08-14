#pragma once

#include <functional>
#include <map>

class KeyboardHandler
{
private:
	std::map<char, std::function<void(float)>> keyMap;

public:
	// Creates a new keyboardhandler
	KeyboardHandler();
	~KeyboardHandler();
	// Ads a key
	// key: The key that is pressed
	// fn: The function that should be ran when the key is
	// pressed, taking a float which is the delta time
	void AddKey(char key, std::function<void(float)> fn);
	// Removes every registered key
	void RemoveAll();
	// Removes a specified key
	// key: char -> The key to remove
	void RemoveKey(char key);
	// Hanles the input of the given key, given the delta time
	// key: char -> The pressed key
	// t: flaot  -> The delta time
	void HandleInput(char key, float t);
};

