#pragma once

#include <vector>
#include <memory>
#include "Model.h"
#include "KeyboardHandler.h"
#include "Camera.h"

class Scene
{
private:
	static GLuint program_id;
	static GLuint uniform_light;

	std::vector<std::shared_ptr<Model>> models;
	Camera camera;
	glm::vec3 light;
	KeyboardHandler keyHandler;

public:
	static void Init(GLuint &program_id);

	Scene();
	~Scene();
	void Render();
	void SetCamera(Camera cam);
	void AddModel(const std::shared_ptr<Model> model);
	void RemoveModel(const std::shared_ptr<Model> model);
	void KeyHandler(unsigned char key, int a, int b);
};

