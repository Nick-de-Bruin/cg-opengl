#include "Mesh.h"

#include <functional>
#include <iostream>

GLuint Mesh::program_id = 0;
GLuint Mesh::simple_program_id = 0;

// Only fetch these variables once for performance
GLuint Mesh::uniform_mat_ambient = 0;
GLuint Mesh::uniform_mat_diffuse = 0;
GLuint Mesh::uniform_mat_specular = 0;
GLuint Mesh::uniform_mat_power = 0;
GLuint Mesh::uniform_mv = 0;
GLuint Mesh::uniform_color = 0;

GLuint Mesh::simple_uniform_mat_ambient = 0;
GLuint Mesh::simple_uniform_mat_diffuse = 0;
GLuint Mesh::simple_uniform_mat_specular = 0;
GLuint Mesh::simple_uniform_mat_power = 0;
GLuint Mesh::simple_uniform_mv = 0;
GLuint Mesh::simple_uniform_color = 0;


Mesh::Mesh()
{
    model = glm::mat4();
    SetColor(162, 164, 164);
}

Mesh::~Mesh() { }

GLuint Mesh::GetTextureId() { return 0; }

void Mesh::Render(const glm::mat4 &view)
{
    glUseProgram(this->GetProgramId());

    for (std::function<glm::mat4(glm::mat4)> transform : transforms) 
        model = transform(model);

    SetUniforms(view);
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

void Mesh::AddTransform(std::function<glm::mat4(glm::mat4)> func)
{
    transforms.push_back(func);
}
