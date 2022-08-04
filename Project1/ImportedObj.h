#pragma once
#include "Mesh.h"
#include "objloader.h"

class ImportedObj :
    public Mesh
{
private:
    GLuint vao;
    ImportedObj();

protected:
    GLuint GetVao();

public:
    ImportedObj(const char* path);
    ImportedObj(const char* objPath, const char* texturePath);
    ImportedObj Copy();
};
