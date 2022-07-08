#pragma once

#include <vector>
#include "Mesh.h"

class PrimitiveModel
{
private:
	std::vector<Mesh*> meshes;

public:
	PrimitiveModel();
	~PrimitiveModel();
	void AddMesh(Mesh mesh);
	void Render();
};

