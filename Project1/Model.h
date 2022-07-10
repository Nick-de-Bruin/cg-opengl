#pragma once

#include <memory>
#include <vector>
#include "Mesh.h"

class Model
{
private:
	std::vector<std::shared_ptr<Mesh>> meshes;

public:
	void Render();
	void AddMesh(const std::shared_ptr<Mesh> mesh);
	void RemoveMesh(const std::shared_ptr<Mesh> mesh);
};

