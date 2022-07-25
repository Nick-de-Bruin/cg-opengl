#include "Cube.h"

bool Cube::initialized = false;

GLuint Cube::GetVao() { return vao; }

Cube::Cube() : Mesh()
{
    if (!initialized)
    {
        initialized = true;
        glGenVertexArrays(1, &vao);
        BindVertices();
        BindNormals();
    }
}
