#version 430 core

// Uniform matrices
uniform mat4 mv;
uniform mat4 projection;
uniform vec3 obj_color;

// Per-vertex inputs
in vec3 position;
in vec3 color;

out vec3 vColor;

void main()
{
	gl_Position = projection * mv * vec4(position, 1.0);

	vColor = obj_color;
}
