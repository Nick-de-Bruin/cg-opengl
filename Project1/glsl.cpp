#include "glsl.h"
#include <fstream>
#include <sstream>

char* glsl::contents;

char* glsl::readFile(const char* filename)
{
    std::ifstream file = std::ifstream(filename);
    std::ostringstream contents;

    contents << file.rdbuf();
    std::string str = contents.str();

    char* ccontents = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ccontents);
    ccontents[str.size()] = '\0';

    return ccontents;
}

bool glsl::compiledStatus(GLint shaderID)
{
    GLint compiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if (compiled) {
        return true;
    }
    else {
        GLint logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        char* msgBuffer = new char[logLength];
        glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
        printf("%s\n", msgBuffer);
        delete[](msgBuffer);
        return false;
    }
}

GLuint glsl::makeVertexShader(const char* shaderSource)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(vertexShaderID);
    bool compiledCorrectly = compiledStatus(vertexShaderID);
    if (compiledCorrectly)
    {
        return vertexShaderID;
    }
    return -1;
}

GLuint glsl::makeFragmentShader(const char* shaderSource)
{
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(fragmentShaderID);
    bool compiledCorrectly = compiledStatus(fragmentShaderID);
    if (compiledCorrectly) 
    {
        return fragmentShaderID;
    }
    return -1;
}

GLuint glsl::makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    GLuint shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShaderID);
    glAttachShader(shaderID, fragmentShaderID);
    glLinkProgram(shaderID);
    return shaderID;
}