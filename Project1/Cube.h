#pragma once
#include "PrimitiveMesh.h"

class Cube :
    public PrimitiveMesh
{
private:
    static GLuint vao;
    static bool initialized;

    static std::vector<GLfloat> vertices;
    static std::vector<GLfloat> colors;
    static std::vector<GLushort> elements;

protected:
    // Returns the VAO of the object
    GLuint GetVao();

public:
    // Renders the object
    // view: mat4 -> The view of the camera
    void Render(const glm::mat4& view);

    // Creates a cube at 0, 0, 0
    Cube();
    // Creates a cube at given coordinates
    // x, y, z: float -> The coordinates
    Cube(float x, float y, float z);
};

