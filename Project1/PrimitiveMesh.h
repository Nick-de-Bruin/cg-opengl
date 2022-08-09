#pragma once
#include "Mesh.h"
class PrimitiveMesh :
    public Mesh
{
protected:
	GLuint GetProgramId();

	void BindElements(
		std::vector<GLfloat> verts, 
		std::vector<GLfloat> colors, 
		std::vector<GLushort> elements
	);

	void SetUniforms(const glm::mat4& view);
};

