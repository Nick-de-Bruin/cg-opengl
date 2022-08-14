#include "MainScene.h"

// Primitives
#include "Cube.h"
#include "Pyramid.h"
#include "ThreePyramid.h"
#include "Plane.h"
#include "PrimitivePolygon.h"
// End primitives
#include "ImportedObj.h"
#include "Material.h"

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
	std::shared_ptr<Mesh> cube_wroof_polygon = std::make_shared<PrimitivePolygon>(0, .375, 0);
	(*cube_wroof_cube).SetColor(200, 60, 60);
	(*cube_wroof_polygon).SetColor(50, 50, 50);
	
	(*cube_with_roof).AddMesh(cube_wroof_cube);
	(*cube_with_roof).AddMesh(cube_wroof_polygon);

	(*cube_with_roof).Move({ 3, 1.75, 0 });
	(*cube_with_roof).Transform([](glm::mat4 model) {
		return glm::scale(model, { 0.25, 0.25, 0.25 });
	});

	(*cube_with_roof).AddTransform(single_axis_rotation);
#pragma endregion cube_with_roof

#pragma region house
	std::shared_ptr<Mesh> house_cube = 
		std::make_shared<Cube>();
	std::shared_ptr<Mesh> house_roof = 
		std::make_shared<PrimitivePolygon>(0, 0.375, 0);
	std::shared_ptr<Mesh> house_chimney = 
		std::make_shared<Cube>(0, 1.25, 0.125);
	std::shared_ptr<Mesh> house_door = 
		std::make_shared<Cube>(0.25, 1.05, 0.125);
	std::shared_ptr<Mesh> house_garden_wall = 
		std::make_shared<Cube>(0.375, 1.35, 0.25);

	(*house_cube).SetColor(200, 60, 60);
	(*house_roof).SetColor(50, 50, 50);
	(*house_chimney).SetColor(200, 60, 60);
	(*house_door).SetColor(50, 100, 50);
	(*house_garden_wall).SetColor(50, 50, 50);

	(*house_chimney).model = glm::scale((*house_chimney).model, { 0.1, 0.5, 0.1 });
	(*house_door).model = glm::scale((*house_door).model, { 0.1, 0.3, 0.2 });
	(*house_garden_wall).model = 
		glm::scale((*house_garden_wall).model, { 0.5, 0.1, 0.1 });

	(*house).AddMesh(house_cube);
	(*house).AddMesh(house_roof);
	(*house).AddMesh(house_chimney);
	(*house).AddMesh(house_door);
	(*house).AddMesh(house_garden_wall);

	(*house).Move({ 0, 1.75, 0 });
	(*house).Transform([](glm::mat4 model) {
		return glm::scale(model, { 0.25, 0.25, 0.25 });
	});

#pragma endregion house

#pragma region pyramids
	std::shared_ptr<Mesh> pyramid = std::make_shared<Pyramid>(-1, 0, 0);
	std::shared_ptr<Mesh> three_pyramid = std::make_shared<ThreePyramid>(1, 0, 0);

	(*pyramid).SetColor(255, 100, 100);
	(*three_pyramid).SetColor(100, 100, 255);

	(*pyramids).AddMesh(pyramid);
	(*pyramids).AddMesh(three_pyramid);

	(*pyramids).Move({0, 1.75, -5});
	(*pyramids).Transform([](glm::mat4 model) {
		return glm::scale(model, { 0.25, 0.25, 0.25 });
	});

	(*pyramids).AddTransform(multi_rotation);
#pragma endregion pyramids

#pragma region plane
	std::shared_ptr<Mesh> plane_mesh = std::make_shared<Plane>();
	(*plane_mesh).SetColor(123, 123, 123);
	
	(*plane).AddMesh(plane_mesh);

	(*plane).Move({ -3, 1.75, 0 });
	(*plane).Transform([](glm::mat4 model) {
		return glm::scale(model, { 0.25, 0.25, 0.25 });
	});

	(*plane).AddTransform(multi_rotation);
#pragma endregion plane

#pragma region cube
	std::shared_ptr<Mesh> cube_mesh = std::make_shared<Cube>();
	(*cube_mesh).SetColor(100, 255, 100);

	(*cube).AddMesh(cube_mesh);

	(*cube).Move({ 0, 1.75, 5 });
	(*cube).Transform([](glm::mat4 model) {
		return glm::scale(model, { 0.25, 0.25, 0.25 });
	});

	(*cube).AddTransform(multi_rotation);
#pragma endregion cube

#pragma region floor
	for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			std::shared_ptr<Mesh> floor_mesh = std::make_shared<ImportedObj>(
				"box.obj", "MarbleFloor.bmp", i * 10, -1.0, j * 10);
			(*floor_mesh).model = glm::scale((*floor_mesh).model, glm::vec3(10, 1, 10));
			(*floor_mesh).material = Material(
				{.1, .1, .1},
				{0.0, 1.0, 0.0},
				{0.0, 0.0, 0.0},
				2
			);
			(*floor).AddMesh(floor_mesh);
		}
	}
#pragma endregion floor

#pragma region walls
	Material wall_mat = Material(
		{0.1, 0.1, 0.1},
		{0.5, 0.3, 0.3},
		{0.3, 0.3, 0.0},
		2
	);

	std::shared_ptr<Mesh> wall_north_bottom =
		std::make_shared<ImportedObj>("box.obj", "WallRepeating.bmp",
			-10, 0, 0);
	std::shared_ptr<Mesh> wall_north_top =
		std::make_shared<ImportedObj>("box.obj", "MarbleWall.bmp",
			-10, 2, 0);

	(*wall_north_top).material = wall_mat;

	(*wall_north_bottom).model = glm::scale((*wall_north_bottom).model,
		{ 0.1, 2.0, 20.0 });
	(*wall_north_top).model = glm::scale((*wall_north_top).model,
		{ 0.1, 2.0, 20.0 });

	(*walls).AddMesh(wall_north_bottom);
	(*walls).AddMesh(wall_north_top);

	std::shared_ptr<Mesh> wall_south_bottom =
		std::make_shared<ImportedObj>("box.obj", "WallRepeating.bmp",
			10, 0, 0);
	std::shared_ptr<Mesh> wall_south_top =
		std::make_shared<ImportedObj>("box.obj", "MarbleWall.bmp",
			10, 2, 0);

	(*wall_south_top).material = wall_mat;

	(*wall_south_bottom).model = glm::scale((*wall_south_bottom).model,
		{ 0.1, 2.0, 20.0 });
	(*wall_south_top).model = glm::scale((*wall_south_top).model,
		{ 0.1, 2.0, 20.0 });

	(*walls).AddMesh(wall_south_bottom);
	(*walls).AddMesh(wall_south_top);

	std::shared_ptr<Mesh> wall_east_bottom =
		std::make_shared<ImportedObj>("box.obj", "WallRepeating.bmp",
			0, 0, 10);
	std::shared_ptr<Mesh> wall_east_top =
		std::make_shared<ImportedObj>("box.obj", "MarbleWall.bmp",
			0, 2, 10);

	(*wall_east_top).material = wall_mat;

	(*wall_east_bottom).model = glm::scale((*wall_east_bottom).model,
		{ 20.0, 2.0, 0.1 });
	(*wall_east_top).model = glm::scale((*wall_east_top).model,
		{ 20.0, 2.0, 0.1 });

	(*walls).AddMesh(wall_east_bottom);
	(*walls).AddMesh(wall_east_top);

	std::shared_ptr<Mesh> wall_west_bottom =
		std::make_shared<ImportedObj>("box.obj", "WallRepeating.bmp",
			0, 0, -10);
	std::shared_ptr<Mesh> wall_west_top =
		std::make_shared<ImportedObj>("box.obj", "MarbleWall.bmp",
			0, 2, -10);

	(*wall_west_top).material = wall_mat;

	(*wall_west_bottom).model = glm::scale((*wall_west_bottom).model,
		{ 20.0, 2.0, 0.1 });
	(*wall_west_top).model = glm::scale((*wall_west_top).model,
		{ 20.0, 2.0, 0.1 });

	(*walls).AddMesh(wall_west_bottom);
	(*walls).AddMesh(wall_west_top);
#pragma endregion walls

#pragma region pillars
	std::shared_ptr<Mesh> pillar =
		std::make_shared<ImportedObj>("Pillar.obj", "WallRepeating.bmp",
			0, 0.6, 0);
	(*pillar).model = glm::scale((*pillar).model, { 0.5, 0.5, 0.5 });
	(*pillars).AddMesh(pillar);
#pragma endregion pillars

	AddModel(cube_with_roof);
	AddModel(house);
	AddModel(pyramids);
	AddModel(plane);
	AddModel(cube);

	AddModel(floor);
	AddModel(walls);

	AddModel(pillars);
}

void MainScene::GenerateCamera(std::vector<GLuint> ids,
	const int& width, const int& height)
{
	camera = new Camera(ids, width, height);
}

void MainScene::GenerateLights(std::vector<GLuint> ids)
{
	light = glm::vec3(0, 5, 0);

	for (GLuint program : ids)
	{
		GLuint uniform_light = glGetUniformLocation(program, "light_pos");

		glUseProgram(program);
		glUniform3fv(uniform_light, 1, glm::value_ptr(light));
	}
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
			walk_position = (*camera).position;
			walk_yaw = (*camera).yaw;
			walk_pitch = (*camera).pitch;
			walk_roll = (*camera).roll;

			(*camera).position = { 0, 10, 0 };

			(*camera).pitch = -89.0;
			(*camera).yaw = 0.0;
			(*camera).roll = 90.0;
		}
		else
		{
			(*camera).position = walk_position;

			(*camera).pitch = walk_pitch;
			(*camera).yaw = walk_yaw;
			(*camera).roll = walk_roll;
		}
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

	GenerateLights(program_ids);
	GenerateCamera(program_ids, width, height);
	GenerateMeshes();
	SetWalkControls();
}
