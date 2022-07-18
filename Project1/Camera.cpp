#include "Camera.h"

Camera::Camera(GLuint program_id, int width, int height)
{
	Projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * width / height,
		0.1f, 20.0f
	);

	// Send the uniform variables for the projection. We don't really have
	// to change this, so everything can be done on the creation of the object
	GLuint uniform_proj = glGetUniformLocation(program_id, "projection");

	glUseProgram(program_id);
	glUniformMatrix4fv(
		uniform_proj,
		1, GL_FALSE, 
		glm::value_ptr(Projection)
	);
}
