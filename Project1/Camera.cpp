#include "Camera.h"
#include <iostream>

void Camera::Process()
{
	// https://learnopengl.com/Getting-started/Camera

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	front = glm::normalize(glm::vec3 {
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	});

	// https://stackoverflow.com/questions/64953941/how-to-implement-the-roll-angle-together-with-yaw-and-pitch-in-glmlookat-funct

	up = {
		cos(glm::radians(roll)),
		sin(glm::radians(roll)),
		0
	};
}

glm::vec3 Camera::FlatFront()
{
	// Fix for camera speed when facing straight down
	float x = front.x;
	float z = front.z;

	float total = abs(x) + abs(z);
	if (total < 0.0001)
		x = 1.0;
	else if (total < 1)
	{
		x *= (1 / total);
		z *= (1 / total);
	}

	return { x, 0, z };
}

glm::mat4 Camera::View()
{
	Process();
	return glm::lookAt(
		position,
		position + front,
		up
	);
}

Camera::Camera() 
{ 
	position = glm::vec3(0.0, 1.75, 0.0);
	front = glm::vec3(0.0, 0.0, -1.0);
	up = glm::vec3(0.0, 1.0, 0.0);

	yaw = -90.0;
	pitch = 0.0;
	roll = 90.0;
}

Camera::Camera(std::vector<GLuint> program_ids, int width, int height) 
	: Camera()
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
