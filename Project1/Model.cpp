#include "Model.h"
#include "Model.h"

void Model::Render()
{
	for (auto const& mesh : meshes)
		(*mesh).Render();
}

void Model::AddMesh(const std::shared_ptr<Mesh> mesh)
{
	meshes.push_back(mesh);
}

void Model::RemoveMesh(const std::shared_ptr<Mesh> mesh)
{
	auto val = std::find(
		meshes.begin(),
		meshes.end(),
		mesh
	);

	if (val != std::end(meshes))
		meshes.erase(val);
}
