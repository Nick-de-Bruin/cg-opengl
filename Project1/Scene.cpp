#include "Scene.h"

Scene::Scene() { }

Scene::~Scene() { }

void Scene::AddModel(const PrimitiveModel model)
{
	primitive_models.push_back(model);
}

void Scene::AddModel(const Model model)
{
	models.push_back(model);
}

void Scene::Render()
{
	// Render each model
	for (Model model : models)
		model.Render();

	// Render each primitive model -> Will render each mesh in the model
	for (PrimitiveModel pModel : primitive_models)
		pModel.Render();
}
