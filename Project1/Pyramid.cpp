#include "Pyramid.h"

bool Pyramid::initialized = false;
GLuint Pyramid::vao = 0;

std::vector<GLfloat> Pyramid::vertices = {
	// Bottom
	-1.0, -0.5, -1.0, // 0
	 1.0, -0.5, -1.0, // 1
	 1.0, -0.5,  1.0, // 2
	-1.0, -0.5,  1.0, // 3

	// Top point
	 0.0,  0.5,  0.0  // 4
};

std::vector<GLfloat> Pyramid::colors = {
	// Bottom colors
	1.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 1.0,

	// Top color
	1.0, 1.0, 1.0
};

std::vector<GLushort> Pyramid::elements = {
	// Bottom
	0,1,2, 1,2,3,

	// Sides
	0,1,4, 1,2,4,
	2,3,4, 3,0,4
};

GLuint Pyramid::GetVao() { return vao; }

Pyramid::Pyramid() : PrimitiveMesh()
{
	if (!initialized)
	{
		initialized = true;
		glGenVertexArrays(1, &vao);

		BindElements(vertices, colors, elements);
	}
}

void Pyramid::Render(const glm::mat4& view)
{
	Mesh::Render(view);

	glBindVertexArray(this->GetVao());
	glDrawElements(GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
