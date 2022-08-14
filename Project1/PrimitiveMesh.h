#pragma once
#include "Mesh.h"
class PrimitiveMesh :
    public Mesh
{
protected:
	// Returns the current program ID
	GLuint GetProgramId();

	// Binds vertices, colors, and elements
	// Vec<GLfloat>: vertices
	// Vec<GLfloat>: colors
	// Vec<GLushort>: elements
	void BindElements(
		std::vector<GLfloat> verts, 
		std::vector<GLfloat> colors, 
		std::vector<GLushort> elements
	);

	// Sets the uniforms for the object
	// mat4: The view of the current camera
	void SetUniforms(const glm::mat4& view);

public:
	// Creates an empty primitive mesh
	PrimitiveMesh();
	// Creates a primitive mesh with a location
	// float: x, y, z
	PrimitiveMesh(float x, float y, float z);
};

