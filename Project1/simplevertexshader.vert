#version 430 core

// Uniform matrices
uniform mat4 mv;
uniform mat4 projection;

// Per-vertex inputs
in vec3 position;
in vec3 color;

out vec3 vColor;

void main()
{
	gl_Position = mv * projection * vec4(position, 1.0);

	vColor = color;
}