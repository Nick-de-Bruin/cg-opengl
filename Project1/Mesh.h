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
	static GLuint simple_uniform_color;

	glm::vec3 color;

	// Returns the VAO of the current object
	virtual GLuint GetVao() = 0;
	// Returns the program ID of the current object
	virtual GLuint GetProgramId() = 0;
	// Returns the texture id of the current object
	virtual GLuint GetTextureId();

	// Sets the uniform for the current object
	// Takes in the view from the current camera
	virtual void SetUniforms(const glm::mat4& view) = 0;

public:
	// Creates an empty mesh
	Mesh();
	// Creates an empty mesh with a position
	// As floats: x, y, z
	Mesh(float x, float y, float z);
	~Mesh();

	// Initializes the static variables
	// Takes in:
	// GLuint: program_id for the main program
	// GLuint: simple_program_id for the primitive mesges
	static void Init(GLuint& program_id, GLuint& simple_program_id);

	// Renders the object
	// Takes a mat4: The view of the current camera
	virtual void Render(const glm::mat4 &view);

	// Sets the colour of the current object:
	// Takes an r, g, b, value as floats
	virtual void SetColor(float r, float g, float b);

	// Adds a transform to the current model, to be played
	// every frame. Takes a function that returns and receives
	// a mat4, the model of the object
	void AddTransform(std::function<glm::mat4(glm::mat4)> func);

	// The mesh's model
	glm::mat4 model;
	// The mesh's material
	Material material;
};
