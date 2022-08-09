#pragma once

#include "Scene.h"

class MainScene : public Scene
{
private:
	void GenerateMeshes();
	void GenerateCamera(std::vector<GLuint> ids, 
		const int& width, const int& height);
	void GenerateLights();
	void SetDroneControls();
	void SetWalkControls();

public:
	MainScene(const int& width, const int& height);
};

