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
	// Processes the current camera
	void Process();
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	// Returns a front that is flat, used for
	// move along a flat plane
	glm::vec3 FlatFront();
	// Returns the view of the camera
	glm::mat4 View();

	float yaw;
	float pitch;
	float roll;

	// Default constructor with nothing
	Camera();

	// Creates a camera
	// Vec<GLuint>: program_ids: The ids to bind the projection to
	// int: width, height of the projection
	Camera(std::vector<GLuint> program_ids, int width, int height);
};

