#include "Mesh.h"

#include <functional>

void Mesh::BindVertices()
{
    BindAttribute(this->vertices, "position");
}

void Mesh::BindNormals()
{
    BindAttribute(this->normals, "normal");
}

void Mesh::SetUniforms(const glm::mat4& view)
{
    glm::mat4 mv = model * view;

    glUseProgram(program_id);
    
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    glUniform3fv(uniform_mat_ambient, 1, glm::value_ptr(material.ambient_color));
    glUniform3fv(uniform_mat_diffuse, 1, glm::value_ptr(material.diffuse_color));
    glUniform3fv(uniform_mat_specular, 1, glm::value_ptr(material.specular));
    glUniform1f(uniform_mat_power, material.specular_power);
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
    for (std::function<glm::mat4(glm::mat4)> transform : transforms) 
        model = transform(model);

    SetUniforms(view);

    glBindVertexArray(this->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::Init(GLuint& program_id)
{
    Mesh::program_id = program_id;

    uniform_mat_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_mat_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_mat_power = glGetUniformLocation(program_id, "mat_power");
    uniform_mat_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_mv = glGetUniformLocation(program_id, "mv");
}

void Mesh::AddTransform(std::function<glm::mat4(glm::mat4)> func)
{
    transforms.push_back(func);
}

