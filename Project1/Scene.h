#pragma once

#include <vector>
#include <memory>
#include "Model.h"
#include "KeyboardHandler.h"
#include "Camera.h"

class Scene
{
private:
	std::vector<std::shared_ptr<Model>> models;
	Camera camera;
	KeyboardHandler keyHandler;

public:
	Scene();
	~Scene();
	void Render();
	void SetCamera(Camera cam);
	void AddModel(const std::shared_ptr<Model> model);
	void RemoveModel(const std::shared_ptr<Model> model);
	void KeyboardHandler(unsigned char key, int a, int b);
};

