#pragma once

#include <vector>
#include "PrimitiveModel.h"
#include "Model.h"

class Scene
{
private:
	std::vector<PrimitiveModel> primitive_models;
	std::vector<Model> models;

public:
	Scene();
	~Scene();
	void AddModel(const PrimitiveModel model);
	void AddModel(const Model model);
	void Render();
};

