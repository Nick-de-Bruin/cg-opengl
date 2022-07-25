#pragma once
#include "Mesh.h"

class Cube :
    public Mesh
{
private:
    static GLuint vao;
    static GLuint vbo;
    static bool initialized;

protected:
    GLuint GetVao();

public:
    Cube();
};

