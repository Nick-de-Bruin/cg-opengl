#include "Cube.h"
#include <iostream>

bool Cube::initialized = false;
GLuint Cube::vao = 0;

GLfloat Cube::vertices[24] = {
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

GLfloat Cube::colors[24] = {
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

GLushort Cube::elements[24] = {
	//0, 1, 2,  0, 2, 3, // Front
	//4, 5, 6,  4, 6, 7, // Back
	//0, 1, 5,  0, 5, 4, // Bottom
	//3, 2, 6,  3, 6, 7, // Top
	//0, 3, 7,  0, 7, 4, // Left
	//1, 2, 6,  1, 6, 5  // Right

	// TODO: Make triangles
	0, 1,  1, 2,  2, 3,  3, 0,  // front
	0, 4,  1, 5,  3, 7,  2, 6,  // front to back
	4, 5,  5, 6,  6, 7,  7, 4   //back
};

GLuint Cube::GetVao() { return vao; }

Cube::Cube() : PrimitiveMesh()
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
    glDrawElements(GL_LINES,
        sizeof(elements) / sizeof(GLushort),
        GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
