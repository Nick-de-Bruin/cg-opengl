#include "Scene.h"
#include <vector>
#include <exception>
#include "KeyboardHandler.h"

Scene::Scene() { }
Scene::~Scene() { }

void Scene::Render() 
{
	for (auto const& model : models)
		(*model).Render(camera.View);
}

void Scene::AddModel(const std::shared_ptr<Model> model)
{
	models.push_back(model);
}

void Scene::RemoveModel(const std::shared_ptr<Model> model)
{
	auto val = std::find(
		models.begin(),
		models.end(),
		model
	);
	
	if (val != std::end(models))
		models.erase(val);
}

void Scene::KeyboardHandler(unsigned char key, int a, int b)
{
	keyHandler.HandleInput(key);
}

void Scene::SetCamera(Camera cam)
{
	camera = cam;
}
