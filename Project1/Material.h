#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular;
    float specular_power = 1.0;

	Material();
    Material(glm::vec3 ambient_color, glm::vec3 diffuse_color,
        glm::vec3 specular, float specular_power);
};

