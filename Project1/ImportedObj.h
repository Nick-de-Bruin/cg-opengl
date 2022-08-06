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
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;

    GLuint texture_id;

    GLuint GetVao();
    GLuint GetProgramId();
    GLuint GetTextureId();

    void BindVertices();
    void BindNormals();
    void BindUVs();
    void SetUniforms(const glm::mat4& view);

public:
    void Render(const glm::mat4& view);

    void SetColor(float r, float g, float b);
    void SetTexture(const char* texturePath);

    ImportedObj(const char* path);
    ImportedObj(const char* objPath, const char* texturePath);
};
