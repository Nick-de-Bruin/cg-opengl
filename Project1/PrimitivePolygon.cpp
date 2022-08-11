#include "PrimitivePolygon.h"

bool PrimitivePolygon::initialized = false;
GLuint PrimitivePolygon::vao = 0;

std::vector<GLfloat> PrimitivePolygon::vertices = {
	// Bottom
	-1.0, -0.5, -1.0, // 0
	 1.0, -0.5, -1.0, // 1
	-1.0, -0.5,  1.0, // 2
	 1.0, -0.5,  1.0,  // 3

	// Top
	-1.0,  0.5,  0.0, // 4
	 1.0,  0.5,  0.0  // 5
};

std::vector<GLfloat> PrimitivePolygon::colors = {
	// Bottom
	1.0, 1.0, 1.0,
	1.0, 1.0, 0.0,
	1.0, 0.0, 1.0,
	0.0, 1.0, 1.0,

	// Top
	0.0, 0.0, 1.0,
	1.0, 0.0, 0.0
};

std::vector<GLushort> PrimitivePolygon::elements = {
	// Bottom
	0,1,2, 1,2,3,

	// Square sides
	0,1,4, 1,4,5,
	2,3,4, 3,4,5,

	// Inner sides
	0,2,4, 1,3,5
};

GLuint PrimitivePolygon::GetVao() { return vao; }

PrimitivePolygon::PrimitivePolygon() : PrimitiveMesh()
{
	if (!initialized)
	{
		initialized = true;
		glGenVertexArrays(1, &vao);

		BindElements(vertices, colors, elements);
	}
}

void PrimitivePolygon::Render(const glm::mat4& view)
{
	Mesh::Render(view);

	glBindVertexArray(this->GetVao());
	glDrawElements(GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
