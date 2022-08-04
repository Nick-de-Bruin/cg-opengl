#include "ImportedObj.h"

GLuint ImportedObj::GetVao()
{
	return vao;
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

ImportedObj ImportedObj::Copy()
{
	ImportedObj obj =  ImportedObj();
	obj.vao = GetVao();
	obj.texture_id = texture_id;
	obj.color = color;
	return obj;
}
