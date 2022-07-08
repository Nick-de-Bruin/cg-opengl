#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "Scene.h"

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.frag";
const char* vertexshader_name = "vertexshader.vert";

unsigned const int DELTA_TIME = 10;

//--------------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------------
struct Lightsource
{
    glm::vec3 position;
};
struct Materials
{
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular;
    float specular_power;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint vao;

// Uniform ID's
GLuint uniform_mv;

// Scene
Scene scene;

// Matrices
glm::mat4 model, view, projection;
glm::mat4 mv;

// Vars
vector<glm::vec3> normals;
vector<glm::vec3> vertices;
vector<glm::vec2> uvs;

Lightsource light;
Materials materials;

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

// TODO: Break this out into new class with ability 
// to set and change keys
void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------
// Keep but move some things out -> And move to new class
void Render()
{
    // The background color of the window
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Clears the specified buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attach to specified program
    glUseProgram(program_id);

    // Do transformation of the model. Should be changed
    // We probably want to change the view (?) based on keyboard
    // inputs. We can just save the camera position for switching
    // cameras in a variable -> Or we could point to different
    // memory by saving a pointer
    model = glm::rotate(model, 0.01f, glm::vec3(0.2f, 1.0f, 0.5f));
    mv = view * model;

    // Send mvp
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    // Change this to send all VAOs?
    // Or just render all of them with a single Render() method
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    // Keep swap to swap buffers, otherwise nothing is rendered
    glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------
void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------
// Move to models
void InitShaders()
{
    // Move shaders to a more generic construct (ENUM or something
    // similar? maybe even just classes)
    char* vertexshader = glsl::readFile(vertexshader_name);
    GLuint vsh_id = glsl::makeVertexShader(vertexshader);

    char* fragshader = glsl::readFile(fragshader_name);
    GLuint fsh_id = glsl::makeFragmentShader(fragshader);

    glAttachShader(program_id, vsh_id);

    // Shader can be really simple, only giving colour or something
    // Can probably use one generic shader
    glAttachShader(program_id, fsh_id);

    glLinkProgram(program_id);
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------
// Move to camera class 
void InitMatrices()
{
    model = glm::mat4();

    view = glm::lookAt(
        glm::vec3(2.0, 2.0, 7.0),  // eye
        // If we want to move the camera around we need to
        // change the center?
        glm::vec3(0.0, 0.0, 0.0),  // center
        glm::vec3(0.0, 1.0, 0.0));  // up

    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 
        0.1f,
        20.0f);

    mv = view * model;
}

//------------------------------------------------------------
// void InitMaterials()
// Allocates and fills buffers
//------------------------------------------------------------
// Move to light class
void InitMaterialLight()
{
    // Adds a single light to a pos
    // refactor this per object
    light.position = glm::vec3(4.0, 4.0, 4.0);

    // Sets the materials of the light
    // refactor this per object
    materials.ambient_color = glm::vec3(0.2, 0.2, 0.1);
    materials.diffuse_color = glm::vec3(0.5, 0.5, 0.5);
    materials.specular = glm::vec3(1, 0, 1);
    materials.specular_power = 10.0;
}

//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------
// Move to objects
// Except maybe the 
void InitBuffers()
{
    GLuint position_id, normal_id;
    GLuint vbo_vertices;
    GLuint vbo_normals;

    // vbo for normals
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER,
        normals.size() * sizeof(glm::vec3),
        &normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(glm::vec3), &vertices[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    normal_id = glGetAttribLocation(program_id, "normal");

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);
    
    // Bind normals to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Stop bind to vao
    glBindVertexArray(0);

    // Make uniform vars -> They are for _everything_
    uniform_mv = glGetUniformLocation(program_id, "mv");
    GLuint uniform_proj = glGetUniformLocation(program_id, "projection");
    GLuint uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
    GLuint uniform_material_ambient = glGetUniformLocation(program_id,
        "mat_ambient");
    GLuint uniform_material_diffuse = glGetUniformLocation(program_id,
        "mat_diffuse");
    GLuint uniform_specular = glGetUniformLocation(
        program_id, "mat_specular");
    GLuint uniform_material_power = glGetUniformLocation(
        program_id, "mat_power");

    // Define model
    // mv = view * model;
    mv = view * model;

    // Send uniform vars
    glUseProgram(program_id);
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
    glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light.position));
    glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(materials.ambient_color));
    glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(materials.diffuse_color));
    glUniform3fv(uniform_specular, 1, glm::value_ptr(materials.specular));
    glUniform1f(uniform_material_power, materials.specular_power);
}

//------------------------------------------------------------
// void InitObjects()
// Initializes objects
//------------------------------------------------------------
// Move into objects
void InitObjects()
{
    loadOBJ(
        "teapot.obj", 
        vertices, 
        uvs,
        normals
    );
}


int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Final Nick de Bruin s1141131");
    
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler); // TODO: Use other keyboard handler
    glutTimerFunc(DELTA_TIME, Render, 0);

    glewInit();

    program_id = glCreateProgram();

    InitMaterialLight(); // Remove
    InitObjects(); // Remove
    InitShaders(); // Remove
    InitMatrices(); // Remove
    InitBuffers(); // Remove (?)

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
