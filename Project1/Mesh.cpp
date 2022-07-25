#include "Mesh.h"

void Mesh::BindVertices()
{
    BindAttribute(this->vertices, "position");
}

void Mesh::BindNormals()
{
    BindAttribute(this->normals, "normal");
}

Mesh::Mesh() { }

// TODO: Check if ref is sound
void Mesh::BindAttribute(const vector<glm::vec3> &arr, const GLchar* attribute)
{
    GLuint vbo;

    // Bind the array to the vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
        arr.size() * sizeof(glm::vec3),
        &arr[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Get the attribute id
    GLuint attribute_id = glGetAttribLocation(program_id, attribute);

    // Bind to vao
    glBindVertexArray(this->GetVao());

    // Bind array to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribute_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::Render(const glm::mat4 &view)
{
    // TODO: Apply transformations
    glm::mat4 mv = view * model;

    // Send mv -> We probbaly wanna do something other than a
    // uniform here, because uniform would be
    // for everything, would be bad:tm:
    // glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    glBindVertexArray(this->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::Init(GLuint& program_id)
{
    Mesh::program_id = program_id;
}

