#include "Mesh.h"

#include <functional>

Mesh::Mesh()
{
    SetColor(162, 164, 164);
}

void Mesh::BindVertices()
{
    BindAttribute(this->vertices, "position");
}

void Mesh::BindNormals()
{
    BindAttribute(this->normals, "normal");
}

void Mesh::BindUVs()
{
    GLuint vbo;

    // vbo for uvs
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
        &uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uv_id = glGetAttribLocation(this->GetProgramId(), "uv");

    // Bind to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uv_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::SetUniforms(const glm::mat4& view)
{
    glm::mat4 mv = model * view;

    glUseProgram(this->GetProgramId());
    
    // Bind textures
    glBindTexture(GL_TEXTURE_2D, texture_id); // Move

    // Bind uniforms
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
    glUniform3fv(uniform_mat_ambient, 1, glm::value_ptr(material.ambient_color));
    glUniform3fv(uniform_mat_diffuse, 1, glm::value_ptr(material.diffuse_color));
    glUniform3fv(uniform_mat_specular, 1, glm::value_ptr(material.specular));
    glUniform1f(uniform_mat_power, material.specular_power);
    glUniform3fv(uniform_color, 1, glm::value_ptr(color));
}

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
    GLuint attribute_id = glGetAttribLocation(this->GetProgramId(), attribute);

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

    // Sometimes add textures

    SetUniforms(view);

    glBindVertexArray(this->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::Init(GLuint& program_id, GLuint& simple_program_id)
{
    Mesh::program_id = program_id;
    Mesh::simple_program_id = simple_program_id;

    // Set normal program IDs
    uniform_mat_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_mat_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_mat_power = glGetUniformLocation(program_id, "mat_power");
    uniform_mat_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_mv = glGetUniformLocation(program_id, "mv");
    uniform_color = glGetUniformLocation(program_id, "color");

    // Set simple program IDs
    simple_uniform_mat_ambient = glGetUniformLocation(simple_program_id, "mat_ambient");
    simple_uniform_mat_diffuse = glGetUniformLocation(simple_program_id, "mat_diffuse");
    simple_uniform_mat_power = glGetUniformLocation(simple_program_id, "mat_power");
    simple_uniform_mat_specular = glGetUniformLocation(simple_program_id, "mat_specular");
    simple_uniform_mv = glGetUniformLocation(simple_program_id, "mv");
    simple_uniform_color = glGetUniformLocation(simple_program_id, "color");
}

// Color in
// rgb, 0 - 255
void Mesh::SetColor(float r, float g, float b)
{
    color = glm::vec3(r / 255, g / 255, b / 255);
}

// Move
void Mesh::SetTexture(const char* path)
{
    texture_id = loadBMP(path);
    // Set color to render the texture fully
    color = glm::vec3(255, 255, 255);
}

void Mesh::AddTransform(std::function<glm::mat4(glm::mat4)> func)
{
    transforms.push_back(func);
}

