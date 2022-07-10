#pragma once

#include "Scene.h"

class MainScene : Scene
{
private:
	void GenerateMeshes();
	void GenerateCamera();
	void GenerateLights();
	static void SetDroneControls();
	static void SetWalkControls();

public:
	MainScene();
	~MainScene();
};

