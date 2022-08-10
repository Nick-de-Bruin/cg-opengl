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
	light = glm::vec3(0, 100, 0);
}

void MainScene::SetWalkControls() 
{
	keyHandler.AddKey('w', [&camera = camera] (float speed) {
		(* camera).position += speed * (*camera).FlatFront();
	});

	keyHandler.AddKey('s', [&camera = camera](float speed) {
		(* camera).position -= speed * (*camera).FlatFront();
	});

	keyHandler.AddKey('a', [&camera = camera](float speed) {
		(*camera).position -= glm::normalize(
			glm::cross((*camera).FlatFront(), (*camera).up)
		) * speed;
	});

	keyHandler.AddKey('d', [&camera = camera](float speed) {
		(*camera).position += glm::normalize(
			glm::cross((*camera).FlatFront(), (*camera).up)
		) * speed;
	});

	keyHandler.AddKey('j', [&camera = camera](float speed) {
		(*camera).yaw -= speed * 10;
	});

	keyHandler.AddKey('l', [&camera = camera](float speed) {
		(*camera).yaw += speed * 10;
	});

	keyHandler.AddKey('i', [&camera = camera](float speed) {
		(*camera).pitch += speed * 10;
	});

	keyHandler.AddKey('k', [&camera = camera](float speed) {
		(*camera).pitch -= speed * 10;
	});

	keyHandler.AddKey('u', [&camera = camera](float speed) {
		(*camera).roll += speed * 100;
	});

	keyHandler.AddKey('o', [&camera = camera](float speed) {
		(*camera).roll -= speed * 100;
	});

	keyHandler.AddKey('v', [&](float speed) {
		(*camera).position = { 0, 4, 0 };
		
		(*camera).pitch = -90.0;
		(*camera).yaw = 0.0;
		(*camera).roll = 90.0;
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
