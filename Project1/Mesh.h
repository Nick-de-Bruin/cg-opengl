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
	static GLuint program_id;

	// Only fetch these variables once for performance
	static GLuint uniform_mat_ambient;
	static GLuint uniform_mat_diffuse;
	static GLuint uniform_mat_specular;
	static GLuint uniform_mat_power;
	static GLuint uniform_mv;
	static GLuint uniform_color;

	std::vector<std::function<glm::mat4(glm::mat4)>> transforms;

	void BindAttribute(const vector<glm::vec3> &arr, const GLchar* attribute);

protected:
	// We'll keep vertices in the .h file, since we don't
	// really need it here. The same might not be true for
	// imported objects, but in that case we can add them
	// to the class itself to make it possible to call them
	// in the render function.
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	GLuint texture_id;
	glm::vec3 color;

	// So we can set a single VAO for objects that only
	// need one; Cubes, for example, can all be rendered
	// with the same static VAO, but different models
	virtual GLuint GetVao() = 0;

	// Methods to bidn vertices and normals to the VAO
	void BindVertices();
	void BindNormals();
	void BindUVs();

	void SetUniforms(const glm::mat4& view);

	// Prevent default constructor
	Mesh();

public:
	void Render(const glm::mat4 &view);

	static void Init(GLuint& program_id);

	Material material;

	void SetColor(float r, float g, float b);
	void SetTexture(const char* path);

	void AddTransform(std::function<glm::mat4(glm::mat4)> func);

	// The model we want of the mesh. This includes things
	// like position and rotation. Public so we can get it 
	// for transforms outside of the mesh
	// We keep this in here so we can transform individual
	// meshes, rather than having to work with entire
	// models
	glm::mat4 model;
};
