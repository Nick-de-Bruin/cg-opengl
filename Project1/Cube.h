#pragma once
#include "PrimitiveMesh.h"

class Cube :
    public PrimitiveMesh
{
private:
    static GLuint vao;
    static bool initialized;

    static GLfloat vertices[24];
    static GLfloat colors[24];
    static GLushort elements[24];

protected:
    GLuint GetVao();

public:
    void Render(const glm::mat4& view);

    Cube();
};

