#pragma once
#include "Mesh.h"
#include "objloader.h"
#include <map>

class ImportedObj :
    public Mesh
{
private:
    GLuint vao;
    ImportedObj();
    std::map<std::string, GLuint> obj_map;
    std::map<std::string, GLuint> bmp_map;

protected:
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;

    GLuint texture_id;

    // Returns the VAO of the current object
    GLuint GetVao();
    // Returns the Program / Shader ID of the current object
    GLuint GetProgramId();
    // Returns the texture ID of the current object
    GLuint GetTextureId();

    // Binds the vertices to the object's VAO
    void BindVertices();
    // Binds the normals to the object's VAO
    void BindNormals();
    // Binds the UVs to the object's VAO
    void BindUVs();
    // Sets the uniforms for the current program,
    // using the active object.
    // Takes the current view from the camera
    void SetUniforms(const glm::mat4& view);

public:
    // Renders the object.
    // Takes the view from the camera
    void Render(const glm::mat4& view);

    // Sets the colour of the object.
    // Takes an rgb value as three floats
    void SetColor(float r, float g, float b);
    // Sets the texture of the object
    // Takes the texture path as a string, in the /Textures/ folder
    void SetTexture(const std::string texturePath);

    // Creates a new object
    // Takes the path as a char string, in /Models/
    ImportedObj(const std::string path);
    // Creates a new object
    // Takes the path to the obj as a char string, in /Models/
    // Takes the path to the bmp as a char string, in /Textures/
    ImportedObj(const std::string objPath, const std::string texturePath);
    // Creates a new object
    // Takes the path to the obj as a char string, in /Models/
    // Takes the location of the object as floats, x,y,z
    ImportedObj(const std::string path,
        float x, float y, float z);
    // Creates a new object
    // Takes the path to the obj as a char string, in /Models/
    // Takes the path to the bmp as a char string, in /Textures/
    // Takes the location of the object as floats, x,y,z
    ImportedObj(const std::string objPath, const std::string texturePath,
        float x, float y, float z);
};
