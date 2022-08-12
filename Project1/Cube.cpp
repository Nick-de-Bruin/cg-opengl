#include "Cube.h"
#include <iostream>

bool Cube::initialized = false;
GLuint Cube::vao = 0;

std::vector<GLfloat> Cube::vertices = {
	// front
	-1.0, -1.0,  1.0, // 0
	 1.0, -1.0,  1.0, // 1
	 1.0,  1.0,  1.0, // 2
	-1.0,  1.0,  1.0, // 3
	// back
	-1.0, -1.0, -1.0, // 4
	 1.0, -1.0, -1.0, // 5
	 1.0,  1.0, -1.0, // 6
	-1.0,  1.0, -1.0  // 7
};

std::vector<GLfloat> Cube::colors = {
	// front colors
	1.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	0.0, 1.0, 1.0,
	1.0, 0.0, 1.0,
	1.0, 0.0, 0.0,
	1.0, 1.0, 0.0
};

std::vector<GLushort> Cube::elements = {
	0,1,2, 0,2,3, // Front
	1,5,6, 1,6,2, // Right
	3,2,6, 3,6,7, // Top
	0,1,5, 0,5,4, // Bottom
	4,5,6, 4,6,7, // Back
	0,4,7, 0,7,3  // Left
};

GLuint Cube::GetVao() { return vao; }

Cube::Cube() : Cube(0, 0, 0) {}

Cube::Cube(float x, float y, float z) 
	: PrimitiveMesh(x, y, z)
{
    if (!initialized)
    {
        initialized = true;
		glGenVertexArrays(1, &vao);
	
		BindElements(vertices, colors, elements);
    }
}

void Cube::Render(const glm::mat4& view)
{
    Mesh::Render(view);

    glBindVertexArray(this->GetVao());
	glDrawElements(GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
