#include "PrimitiveMesh.h"

GLuint PrimitiveMesh::GetProgramId() { return program_id; }

void PrimitiveMesh::BindElements(GLfloat* verts, GLfloat* colors, GLushort* elements)
{
    GLuint vbo_vertices;
    GLuint vbo_colors;
    GLuint vbo_elements;

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for elements
    glGenBuffers(1, &vbo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements),
        elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Get vertex attributes
    GLuint position_id = glGetAttribLocation(program_id, "position");
    GLuint color_id = glGetAttribLocation(program_id, "color");

    // Bind to vao
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_elements);

    // Stop bind to vao
    glBindVertexArray(0);
}

void PrimitiveMesh::SetUniforms(const glm::mat4& view)
{
	glm::mat4 mv = model * view;

	glBindTexture(GL_TEXTURE_2D, 0);

	// Bind uniforms
	glUniformMatrix4fv(simple_uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
	glUniform3fv(simple_uniform_mat_ambient, 1, glm::value_ptr(material.ambient_color));
	glUniform3fv(simple_uniform_mat_diffuse, 1, glm::value_ptr(material.diffuse_color));
	glUniform3fv(simple_uniform_mat_specular, 1, glm::value_ptr(material.specular));
	glUniform1f(simple_uniform_mat_power, material.specular_power);
	glUniform3fv(simple_uniform_color, 1, glm::value_ptr(color));
}
