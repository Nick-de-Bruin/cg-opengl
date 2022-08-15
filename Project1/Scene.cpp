#include "Scene.h"
#include <vector>
#include <exception>
#include <iostream>

GLuint Scene::program_id = 0;
GLuint Scene::simple_program_id = 0;

Scene::Scene() {}

void Scene::Render() 
{
	glClearColor(0.5, 0.7, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto const& model : models)
		(*model).Render((*camera).View());

	glutSwapBuffers();
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

void Scene::KeyHandler(unsigned char key, int a, int b, float t)
{
	keyHandler.HandleInput(key, t);
}

void Scene::SetCamera(Camera cam)
{
	camera = &cam;
}
