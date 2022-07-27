#include "Material.h"

Material::Material() { }

Material::Material(glm::vec3 ambient_color, glm::vec3 diffuse_color, glm::vec3 specular, float specular_power)
{
	this->ambient_color = ambient_color;
	this->diffuse_color = diffuse_color;
	this->specular = specular;
	this->specular_power = specular_power;
}
