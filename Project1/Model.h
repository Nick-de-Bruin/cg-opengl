#pragma once

#include <memory>
#include <vector>
#include "Mesh.h"

class Model
{
private:
	std::vector<std::shared_ptr<Mesh>> meshes;

public:
	// Renders the current model
	// Takes the view of the current camera
	void Render(const glm::mat4 &view);
	// Adds a mesh
	// Takes a shared pointer to the mesh
	void AddMesh(const std::shared_ptr<Mesh> mesh);
	// Removes a mesh
	// Takes a shared pointer to the mesh
	void RemoveMesh(const std::shared_ptr<Mesh> mesh);
	// Adds a transform to each object in the model
	// Takes a function which receives and returns a mat4,
	// The model of the object
	void AddTransform(std::function<glm::mat4(glm::mat4)> func);

	// Moves the model
	// vec3: Where to move the model
	void Move(glm::vec3 dist);
	// Transforms a model once
	// Takes a function which takes and returns a mat4
	// which is the model of the mesh
	void Transform(std::function<glm::mat4(glm::mat4)> func);
};
