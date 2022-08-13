#include "MainScene.h"

// Primitives
#include "Cube.h"
#include "Pyramid.h"
#include "ThreePyramid.h"
#include "Plane.h"
#include "PrimitivePolygon.h"
// End primitives
#include "ImportedObj.h"

#include <iostream>

void MainScene::GenerateMeshes()
{
	std::shared_ptr<Model> cube_with_roof = std::make_shared<Model>(); // Rotate
	// Don't move at all, as it's likely to break it
	std::shared_ptr<Model> house = std::make_shared<Model>();
	std::shared_ptr<Model> pyramids = std::make_shared<Model>(); // Rotate multi
	std::shared_ptr<Model> plane = std::make_shared<Model>(); // Rotate multi
	std::shared_ptr<Model> cube = std::make_shared<Model>(); // Rotate multi
	// Make imported objects for texture and lighting
	std::shared_ptr<Model> floor = std::make_shared<Model>(); 
	std::shared_ptr<Model> walls = std::make_shared<Model>();
	// Pillars should also be below the other objects we're placing
	std::shared_ptr<Model> pillars = std::make_shared<Model>();

#pragma region rotation_functions
	auto multi_rotation = [](glm::mat4 model) {
		return glm::rotate(
			model,
			glm::radians(1.0f),
			glm::vec3(0.0, 0.5, 1.0)
		);
	};
	auto single_axis_rotation = [](glm::mat4 model) {
		return glm::rotate(
			model,
			glm::radians(1.0f),
			glm::vec3(0.0, 1.0, 0.0)
		);
	};
#pragma endregion rotation_functions

	// TODO: Add positions to each element
	// Add position to each model
	// Add scale to each element
	// Add scale to each model
	
#pragma region cube_with_roof
	std::shared_ptr<Mesh> cube_wroof_cube = std::make_shared<Cube>();
	std::shared_ptr<Mesh> cube_wroof_polygon = std::make_shared<PrimitivePolygon>();
	(*cube_with_roof).AddMesh(cube_wroof_cube);
	(*cube_with_roof).AddMesh(cube_wroof_polygon);
	(*cube_with_roof).AddTransform(single_axis_rotation);
#pragma endregion cube_with_roof

#pragma region house
	std::shared_ptr<Mesh> house_cube = std::make_shared<Cube>();
	std::shared_ptr<Mesh> house_roof = std::make_shared<PrimitivePolygon>();
	std::shared_ptr<Mesh> house_chimney = std::make_shared<Cube>();
	std::shared_ptr<Mesh> house_door = std::make_shared<Cube>();
	std::shared_ptr<Mesh> house_garden_wall = std::make_shared<Cube>();

	(*house).AddMesh(house_cube);
	(*house).AddMesh(house_roof);
	(*house).AddMesh(house_chimney);
	(*house).AddMesh(house_door);
	(*house).AddMesh(house_garden_wall);
#pragma endregion house

#pragma region pyramids
	std::shared_ptr<Mesh> pyramid = std::make_shared<Pyramid>();
	std::shared_ptr<Mesh> three_pyramid = std::make_shared<ThreePyramid>();

	(*pyramids).AddMesh(pyramid);
	(*pyramids).AddMesh(three_pyramid);
	(*pyramids).AddTransform(multi_rotation);
#pragma endregion pyramids

#pragma region plane
	std::shared_ptr<Mesh> plane_mesh = std::make_shared<Plane>();
	(*plane_mesh).AddTransform(multi_rotation);
	(*plane).AddMesh(plane_mesh);
#pragma endregion plane

#pragma region cube
	std::shared_ptr<Mesh> cube_mesh = std::make_shared<Cube>(); 
	(*cube_mesh).AddTransform(multi_rotation);
	(*cube).AddMesh(cube_mesh);
#pragma endregion cube

#pragma region floor
	for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			std::shared_ptr<Mesh> floor_mesh = std::make_shared<ImportedObj>(
				"box.obj", "Yellobrk.bmp", i * 10, -1.0, j * 10);
			(*floor_mesh).model = glm::scale((*floor_mesh).model, glm::vec3(10, 1, 10));
			(*floor).AddMesh(floor_mesh);
		}
	}
#pragma endregion floor

#pragma region walls

#pragma endregion walls

#pragma region pillars

#pragma endregion pillars

	//AddModel(cube_with_roof);
	//AddModel(house);
	//AddModel(pyramids);
	//AddModel(plane);
	//AddModel(cube);

	AddModel(floor);
	AddModel(walls);

	AddModel(pillars);
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
		if ((*camera).position.y < 2) {
			(*camera).position = { 0, 10, 0 };

			(*camera).pitch = -89.0;
			(*camera).yaw = 0.0;
		}
		else
		{
			(*camera).position = { 0, 1.75, 0 };

			(*camera).pitch = 0.0;
			(*camera).yaw = -90.0;
		}
		
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
