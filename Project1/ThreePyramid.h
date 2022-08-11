#pragma once
#include "PrimitiveMesh.h"
class ThreePyramid :
    public PrimitiveMesh
{
private:
    static GLuint vao;
    static bool initialized;

    static std::vector<GLfloat> vertices;
    static std::vector<GLfloat> colors;
    static std::vector<GLushort> elements;

protected:
    GLuint GetVao();

public:
    void Render(const glm::mat4& view);

    ThreePyramid();
};

