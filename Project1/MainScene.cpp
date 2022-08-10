#include "MainScene.h"

#include "Cube.h"
#include <iostream>

void MainScene::GenerateMeshes()
{
	std::shared_ptr<Model> cube = std::make_shared<Model>();
	std::shared_ptr<Mesh> c = std::make_shared<Cube>();
	(*c).AddTransform([](glm::mat4 model) {
		return glm::rotate(
			model,
			glm::radians(1.0f),
			glm::vec3(0.0f, 0.5f, 1.0f)
		);
	});
	(* cube).AddMesh(c);
	AddModel(cube);
}

void MainScene::GenerateCamera(std::vector<GLuint> ids,
	const int& width, const int& height)
{
	camera = new Camera(ids, width, height);
}

void MainScene::GenerateLights()
{
	// TODO
}

void MainScene::SetDroneControls() 
{ 
}

void MainScene::SetWalkControls() 
{
	keyHandler.AddKey('w', [&camera = camera] (float speed) {
		(* camera).position += speed * (*camera).front;
	});

	keyHandler.AddKey('s', [&camera = camera](float speed) {
		(*camera).position -= speed * (*camera).front;
	});

	keyHandler.AddKey('a', [&camera = camera](float speed) {
		(*camera).position -= glm::normalize(
			glm::cross((*camera).front, (*camera).up)
		) * speed;
	});

	keyHandler.AddKey('d', [&camera = camera](float speed) {
		(*camera).position += glm::normalize(
			glm::cross((*camera).front, (*camera).up)
		) * speed;
	});
}

MainScene::MainScene(const int &width, const int &height)
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
	GenerateCamera(program_ids, width, height);
	GenerateMeshes();
	SetWalkControls();
}
