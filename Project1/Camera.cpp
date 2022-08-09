#include "Camera.h"

Camera::Camera() { }

Camera::Camera(std::vector<GLuint> program_ids, int width, int height)
{
	Projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * width / height,
		0.1f,
		20.0f
	);

	for (GLuint id : program_ids)
	{
		// Send the uniform variables for the projection. We don't really have
		// to change this, so everything can be done on the creation of the object
		GLuint uniform_proj = glGetUniformLocation(id, "projection");

		glUseProgram(id);
		glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(Projection));
	}
}
