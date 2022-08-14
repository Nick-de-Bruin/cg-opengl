#pragma once

#include "Scene.h"

class MainScene : public Scene
{
private:
	void GenerateMeshes();
	void GenerateCamera(std::vector<GLuint> ids, 
		const int& width, const int& height);
	void GenerateLights(std::vector<GLuint> ids);
	void SetWalkControls();

	glm::vec3 walk_position;
	float walk_yaw;
	float walk_pitch;
	float walk_roll;

public:
	// Constructs the main scene
	// Takes int: width, height of the projection
	MainScene(const int& width, const int& height);
};

