#include "PrimitiveMesh.h"
#include <iostream>

GLuint PrimitiveMesh::GetProgramId() { return simple_program_id; }

void PrimitiveMesh::BindElements(
    std::vector<GLfloat> verts, 
    std::vector<GLfloat> colors, 
    std::vector<GLushort> elements)
{
    glUseProgram(this->GetProgramId());

    GLuint vbo_vertices;
    GLuint vbo_colors;
    GLuint ibo_elements;

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, 
        verts.size() * sizeof(GLfloat),
        &verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, 
        colors.size() * sizeof(GLfloat),
        &colors[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for elements
    glGenBuffers(1, &ibo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
        elements.size() * sizeof(GLushort),
        &elements[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Get vertex attributes
    GLuint position_id = glGetAttribLocation(this->GetProgramId(), "position");
    GLuint color_id = glGetAttribLocation(this->GetProgramId(), "color");

    glBindVertexArray(this->GetVao());

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind colors to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind elements to vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);

    // Stop bind to vao
    glBindVertexArray(0);
}

void PrimitiveMesh::SetUniforms(const glm::mat4& view)
{
	glm::mat4 mv = view * model;

	glBindTexture(GL_TEXTURE_2D, 0);

	// Bind uniforms
	glUniformMatrix4fv(simple_uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
    glUniform3fv(simple_uniform_color, 1, glm::value_ptr(color));
}

PrimitiveMesh::PrimitiveMesh() : Mesh() 
{ 
    glUseProgram(this->GetProgramId());
}

PrimitiveMesh::PrimitiveMesh(float x, float y, float z)
    : Mesh(x, y, z) 
{
    glUseProgram(this->GetProgramId());
}
