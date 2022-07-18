#pragma once

#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"

class Mesh
{
private:
	// Could be static, but this would mean moving it all
	// into the inherited classes, and we're working with
	// a small enough batch size that it shouldn't really
	// matter
	GLuint vao;
	GLuint vbo;

	// We'll keep vertices in the .h file, since we don't
	// really need it here. The same might not be true for
	// imported objects, but in that case we can add them
	// to the class itself to make it possible to call them
	// in the render function.
	vector<glm::vec3> vertices;
	
	// Prevent construction of a mesh without anything
	// bound to it
	Mesh();

public:
	void Render(const glm::mat4 &view);

	// The model we want of the mesh. This includes things
	// like position and rotation.
	// Public so we can get it for transforms outside of
	// the mesh
	// We keep this in here so we can transform individual
	// meshes, rather than having to work with entire
	// models
	glm::mat4 model;
};
