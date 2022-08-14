#include "Model.h"
#include "Model.h"

void Model::Render(const glm::mat4 &view)
{
	for (auto const& mesh : meshes)
		(*mesh).Render(view);
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

void Model::AddTransform(std::function<glm::mat4(glm::mat4)> func)
{
	for (std::shared_ptr<Mesh> mesh : meshes)
		(*mesh).AddTransform(func);
}

void Model::Move(glm::vec3 dist)
{
	for (std::shared_ptr<Mesh> mesh : meshes)
		(*mesh).model = glm::translate((*mesh).model, dist);
}

void Model::Transform(std::function<glm::mat4(glm::mat4)> func)
{
	for (std::shared_ptr<Mesh> mesh : meshes)
		(*mesh).model = func((*mesh).model);
}
