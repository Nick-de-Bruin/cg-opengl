#pragma once

#include <vector>
#include <functional>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "Material.h"
#include "texture.h"

class Mesh
{
private:
	std::vector<std::function<glm::mat4(glm::mat4)>> transforms;

protected:
	static GLuint program_id;
	static GLuint simple_program_id;

	// Only fetch these variables once for performance
	static GLuint uniform_mat_ambient;
	static GLuint uniform_mat_diffuse;
	static GLuint uniform_mat_specular;
	static GLuint uniform_mat_power;
	static GLuint uniform_mv;
	static GLuint uniform_color;
	static GLuint uniform_texsampler;
	static GLuint simple_uniform_mv;

	glm::vec3 color;

	// So we can set a single VAO for objects that only
	// need one; Cubes, for example, can all be rendered
	// with the same static VAO, but different models
	virtual GLuint GetVao() = 0;
	virtual GLuint GetProgramId() = 0;
	virtual GLuint GetTextureId();

	virtual void SetUniforms(const glm::mat4& view) = 0;

public:
	Mesh();
	Mesh(float x, float y, float z);
	~Mesh();

	static void Init(GLuint& program_id, GLuint& simple_program_id);

	virtual void Render(const glm::mat4 &view);
	virtual void SetColor(float r, float g, float b);

	void AddTransform(std::function<glm::mat4(glm::mat4)> func);

	// The model we want of the mesh. This includes things
	// like position and rotation. Public so we can get it 
	// for transforms outside of the mesh
	// We keep this in here so we can transform individual
	// meshes, rather than having to work with entire
	// models
	glm::mat4 model;
	Material material;
};
