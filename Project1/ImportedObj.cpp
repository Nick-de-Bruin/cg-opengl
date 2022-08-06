#include "ImportedObj.h"

GLuint ImportedObj::GetVao() { return vao; }
GLuint ImportedObj::GetProgramId() { return program_id; }
GLuint ImportedObj::GetTextureId() { return texture_id; }

void ImportedObj::Render(const glm::mat4& view)
{
	Mesh::Render(view);

	glBindVertexArray(this->GetVao());
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

ImportedObj::ImportedObj(const char* path)
{
	glGenVertexArrays(1, &vao);
	loadOBJ(path, vertices, uvs, normals);
	SetColor(162, 164, 164);
	BindVertices();
	BindNormals();
	BindUVs();
}

ImportedObj::ImportedObj(const char* objPath, const char* texturePath)
{
	glGenVertexArrays(1, &vao);
	loadOBJ(objPath, vertices, uvs, normals);
	SetTexture(texturePath);
	BindVertices();
	BindNormals();
	BindUVs();
}

void ImportedObj::BindVertices()
{
	GLuint vbo;

	// Bind the array to the vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(glm::vec3),
		&vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get the attribute id
	GLuint attribute_id = glGetAttribLocation(this->GetProgramId(), "position");

	// Bind to vao
	glBindVertexArray(this->GetVao());

	// Bind array to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void ImportedObj::BindNormals()
{
	GLuint vbo;

	// Bind the array to the vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(glm::vec3),
		&normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get the attribute id
	GLuint attribute_id = glGetAttribLocation(this->GetProgramId(), "normal");

	// Bind to vao
	glBindVertexArray(this->GetVao());

	// Bind array to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void ImportedObj::BindUVs()
{
	GLuint vbo;

	// vbo for uvs
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 
		uvs.size() * sizeof(glm::vec2),
		&uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint uv_id = glGetAttribLocation(this->GetProgramId(), "uv");

	glBindVertexArray(this->GetVao());

	// Bind to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uv_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void ImportedObj::SetUniforms(const glm::mat4& view)
{
	glm::mat4 mv = model * view;

	// Bind textures
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Bind uniforms
	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
	glUniform3fv(uniform_mat_ambient, 1, glm::value_ptr(material.ambient_color));
	glUniform3fv(uniform_mat_diffuse, 1, glm::value_ptr(material.diffuse_color));
	glUniform3fv(uniform_mat_specular, 1, glm::value_ptr(material.specular));
	glUniform1f(uniform_mat_power, material.specular_power);
	glUniform3fv(uniform_color, 1, glm::value_ptr(color));
}

void ImportedObj::SetColor(float r, float g, float b)
{
	// Set to base white texture
	texture_id = loadBMP("w.bmp");
	color = glm::vec3(r / 255, g / 255, b / 255);
}

void ImportedObj::SetTexture(const char* texturePath)
{
	texture_id = loadBMP(texturePath);
	// Set color to render the texture fully
	color = glm::vec3(255, 255, 255);
}

