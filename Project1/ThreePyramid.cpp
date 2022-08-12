#include "ThreePyramid.h"

bool ThreePyramid::initialized = false;
GLuint ThreePyramid::vao = 0;

std::vector<GLfloat> ThreePyramid::vertices = {
	// Bottom
	 1.0, -0.5,  1.0, // 0
	-1.0, -0.5, -1.0, // 1
	-1.0, -0.5,  1.0, // 2

	// Top
	 0.0,  0.5,  0.0  // 3
};

std::vector<GLfloat> ThreePyramid::colors = {
	// Bottom
	1.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,

	// Top
	1.0, 1.0, 1.0
};

std::vector<GLushort> ThreePyramid::elements = {
	// Bottom
	0,1,2,

	// Sides
	0,1,3,
	1,2,3,
	2,0,3
};

GLuint ThreePyramid::GetVao() { return vao; }

ThreePyramid::ThreePyramid() : ThreePyramid(0, 0, 0) {}

ThreePyramid::ThreePyramid(float x, float y, float z) 
	: PrimitiveMesh(x, y, z)
{
	if (!initialized)
	{
		initialized = true;
		glGenVertexArrays(1, &vao);

		BindElements(vertices, colors, elements);
	}
}

void ThreePyramid::Render(const glm::mat4& view)
{
	Mesh::Render(view);

	glBindVertexArray(this->GetVao());
	glDrawElements(GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
