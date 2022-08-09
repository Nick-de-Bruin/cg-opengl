#include "MainScene.h"

#include "Cube.h"
#include <iostream>

void MainScene::GenerateMeshes()
{
	std::shared_ptr<Model> cube = std::make_shared<Model>();
	std::shared_ptr<Mesh> c = std::make_shared<Cube>();
	(* cube).AddMesh(c);
	AddModel(cube);
}

void MainScene::GenerateCamera(std::vector<GLuint> ids)
{
	camera = Camera(ids, 800, 600);
	camera.View = glm::lookAt(
		glm::vec3(2.0, 2.0, 7.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0)
	);
}

void MainScene::GenerateLights()
{
	// TODO
}

void MainScene::SetDroneControls() { }
void MainScene::SetWalkControls() { }

MainScene::MainScene()
{
	program_id = glsl::makeShaderProgram(
		glsl::makeVertexShader(
			glsl::readFile("vertexshader.vert")),
		glsl::makeFragmentShader(
			glsl::readFile("fragmentshader.frag"))
	);

	simple_program_id = glsl::makeShaderProgram(
		glsl::makeVertexShader(
			glsl::readFile("simplevertexshader.vert")),
		glsl::makeFragmentShader(
			glsl::readFile("simplefragmentshader.frag"))
	);

	std::vector<GLuint> program_ids	{ program_id, simple_program_id };

	Mesh::Init(program_id, simple_program_id);

	GenerateLights();
	GenerateCamera(program_ids);
	GenerateMeshes();
}
