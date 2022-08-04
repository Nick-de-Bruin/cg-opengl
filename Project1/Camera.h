#pragma once

#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	// We don't really want to change the projection
	// for this project, so just make it private
	glm::mat4 Projection;

public:
	glm::mat4 View;

	// Default constructor with nothing
	Camera();

	Camera(GLuint program_id, int width, int height);
};

