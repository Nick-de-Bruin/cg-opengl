#include "Plane.h"

bool Plane::initialized = false;
GLuint Plane::vao = 0;

std::vector<GLfloat> Plane::vertices = {
	-1.0, 0.0, -1.0, // 0
	 1.0, 0.0, -1.0, // 1
	-1.0, 0.0,  1.0, // 2
	 1.0, 0.0,  1.0  // 3
};

std::vector<GLfloat> Plane::colors = {
	1.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0
};

std::vector<GLushort> Plane::elements = {
	0,1,2, 1,2,3
};

GLuint Plane::GetVao() { return vao; }

Plane::Plane() : Plane(0, 0, 0) {}

Plane::Plane(float x, float y, float z) 
	: PrimitiveMesh(x, y, z)
{
	if (!initialized)
	{
		initialized = true;
		glGenVertexArrays(1, &vao);

		BindElements(vertices, colors, elements);
	}
}

void Plane::Render(const glm::mat4& view)
{
	glUseProgram(this->GetProgramId());

	Mesh::Render(view);

	glBindVertexArray(this->GetVao());
	glDrawElements(GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
