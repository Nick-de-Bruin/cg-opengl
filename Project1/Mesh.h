#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Material 
{
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float specular_power = 1.0;
};

class Mesh
{
private:
	GLuint vao;

	GLuint vbo_vertices;
	GLuint vbo_colors;
	GLuint vbo_elements;
	GLuint vbo_uvs;
	GLuint vbo_normals;

	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	GLuint position_id;
	GLuint normal_id;
	GLuint color_id;
	GLuint uv_id;

	GLuint* program_id;

	void BindToVAO();
	Mesh(GLuint* program_id);
	Mesh(); // Prevent basic construction

public:
	~Mesh();
	void Render();
};

