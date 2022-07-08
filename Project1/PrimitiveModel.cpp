#include "PrimitiveModel.h"
#include "Mesh.h"

PrimitiveModel::PrimitiveModel() { }

PrimitiveModel::~PrimitiveModel()
{
	for (Mesh* mesh : meshes)
	{
		if (mesh != nullptr)
			delete mesh;
	}
}

void PrimitiveModel::AddMesh(Mesh mesh)
{
	meshes.push_back(&mesh);
}

void PrimitiveModel::Render()
{
	for (Mesh* mesh : meshes)
		mesh->Render();
}
