#include "ImportedObj.h"
#include <string>
#include <iostream>

GLuint ImportedObj::GetVao() { return vao; }
GLuint ImportedObj::GetProgramId() { return program_id; }
GLuint ImportedObj::GetTextureId() { return texture_id; }

void ImportedObj::Render(const glm::mat4& view)
{
	glUseProgram(this->GetProgramId());

	Mesh::Render(view);

	//GLint p = 0;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &p);
	//
	//std::cout << "Desired p: " << this->GetProgramId() << std::endl;
	//std::cout << " Actual p: " << p << std::endl;

	glBindVertexArray(this->GetVao());
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

ImportedObj::ImportedObj(const std::string path) 
	: ImportedObj(path, 0, 0, 0) { }

ImportedObj::ImportedObj(const std::string objPath, const std::string texturePath)
	: ImportedObj(objPath, texturePath, 0, 0, 0) { }

ImportedObj::ImportedObj(const std::string path, 
	float x, float y, float z)
	: Mesh(x, y, z)
{
	glUseProgram(this->GetProgramId());

	if (obj_map.count(path) > 0)
		vao = obj_map[path];
	else
	{
		std::string objFolder = "Models/";
		objFolder.append(path);
		glGenVertexArrays(1, &vao);
		loadOBJ(objFolder.c_str(),
			vertices, uvs, normals);
		BindVertices();
		BindNormals();
		BindUVs();

		obj_map[path] = vao;
	}
	SetColor(162, 164, 164);
}

ImportedObj::ImportedObj(const std::string objPath, const std::string texturePath, 
	float x, float y, float z)
	: Mesh(x, y, z)
{
	glUseProgram(this->GetProgramId());

	if (obj_map.count(objPath) > 0)
		vao = obj_map[objPath];
	else
	{
		std::string objFolder = "Models/";
		objFolder.append(objPath);
		glGenVertexArrays(1, &vao);
		loadOBJ(objFolder.c_str(),
			vertices, uvs, normals);
		BindVertices();
		BindNormals();
		BindUVs();

		obj_map[objPath] = vao;
	}

	SetTexture(texturePath);
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
	glm::mat4 mv = view * model;

	// Bind textures
	glActiveTexture(GL_TEXTURE0); // Match up with bind uniform
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glUniform1i(uniform_texsampler, 0);

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
	glUseProgram(this->GetProgramId());

	if (bmp_map.count("w.bmp") > 0)
		texture_id = bmp_map["w.bmp"];
	else
	{
		std::string path = "Textures/";
		path.append("w.bmp");
		texture_id = loadBMP(path.c_str());

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		bmp_map["w.bmp"] = texture_id;
	}

	color = glm::vec3(r / 255, g / 255, b / 255);
}

void ImportedObj::SetTexture(const std::string texturePath)
{
	glUseProgram(this->GetProgramId());

	if (bmp_map.count(texturePath) > 0)
		texture_id = bmp_map[texturePath];
	else
	{
		std::string path = "Textures/";
		path.append(texturePath);
		texture_id = loadBMP(path.c_str());

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		bmp_map[texturePath] = texture_id;
	}

	// Set color to render the texture fully
	color = glm::vec3(255, 255, 255);
}
