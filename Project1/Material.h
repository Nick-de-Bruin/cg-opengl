#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
    // The ambient colour
    glm::vec3 ambient_color;
    // The diffuse colour
    glm::vec3 diffuse_color;
    // The specular colour
    glm::vec3 specular;
    // The power of the specular mapping
    float specular_power = 1.0;

    // Creates a new empty material
	Material();
    // Creates a new material given:
    // vec3: Ambient color
    // vec3: diffuse color
    // vec3: specular color
    // float: Specular power
    Material(glm::vec3 ambient_color, glm::vec3 diffuse_color,
        glm::vec3 specular, float specular_power);
};

