#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "Scene.h"

const int WIDTH = 800, HEIGHT = 600;
unsigned const int DELTA_TIME = 10;

GLuint program_id;
Scene scene;

// TODO: Create and render current scene

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Final Nick de Bruin s1141131");
    
    glutDisplayFunc(Render);
    // glutKeyboardFunc(keyboardHandler); // TODO: Use other keyboard handler
    glutTimerFunc(DELTA_TIME, Render, 0);
    glewInit();

    program_id = glCreateProgram();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    ShowWindow(
        GetConsoleWindow(),
        SW_HIDE
    );

    glutMainLoop();

    return 0;
}

void Render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program_id);
    glutSwapBuffers();
}

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}
