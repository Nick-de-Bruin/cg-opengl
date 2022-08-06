#pragma once

#include "Scene.h"

class MainScene : public Scene
{
private:
	void GenerateMeshes();
	void GenerateCamera(std::vector<GLuint> ids);
	void GenerateLights();
	void SetDroneControls();
	void SetWalkControls();

public:
	MainScene();
};

