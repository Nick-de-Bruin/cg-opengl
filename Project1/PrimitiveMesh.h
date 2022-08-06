#pragma once
#include "Mesh.h"
class PrimitiveMesh :
    public Mesh
{
protected:
	GLuint GetProgramId();

	void BindElements(GLfloat* verts, GLfloat* colors, GLushort* elements);

	void SetUniforms(const glm::mat4& view);
};

