#pragma once

#include <vector>
#include <memory>
#include "Model.h"
#include "KeyboardHandler.h"
#include "Camera.h"

class Scene
{
protected:
	static GLuint program_id;
	static GLuint simple_program_id;
	static GLuint uniform_light;

	std::vector<std::shared_ptr<Model>> models;
	glm::vec3 light;
	KeyboardHandler keyHandler;

public:
	Camera* camera;

	// Creates a new scene
	Scene();
	// Renders the current scene
	void Render();
	// Sets the camera for the current scene
	// Camera: new camera to use
	void SetCamera(Camera cam);
	// Adds a model to the current scene
	// Model: A shared pointer to the model to add
	void AddModel(const std::shared_ptr<Model> model);
	// Removes a model from the scene
	// Model: A shared pointer to the model to remove
	void RemoveModel(const std::shared_ptr<Model> model);
	// Manages the handling of keys
	// Used in main
	// uchar: key which is pressed
	// int:   a, b 
	// float: t, the delta time that has passed
	void KeyHandler(unsigned char key, int a, int b, float t);
};

