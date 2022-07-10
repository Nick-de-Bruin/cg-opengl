#pragma once

#include <vector>
#include <memory>
#include "Model.h"
#include "KeyboardHandler.h"

class Scene
{
private:
	std::vector<std::shared_ptr<Model>> models;
	KeyboardHandler keyHandler;

public:
	Scene();
	~Scene();
	void Render();
	void AddModel(const std::shared_ptr<Model> model);
	void RemoveModel(const std::shared_ptr<Model> model);
	void KeyboardHandler(unsigned char key, int a, int b);
};

