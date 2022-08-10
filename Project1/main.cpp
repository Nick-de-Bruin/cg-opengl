#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "MainScene.h"

const int WIDTH = 800, HEIGHT = 600;
unsigned const int DELTA_TIME = 10;

Scene scene;
float lastFrame = 0.0;
float deltaTime = 0.0;

void KeyboardHandler(unsigned char key, int a, int b) 
{
    scene.KeyHandler(key, a, b, deltaTime); 
}

// Not sure why we need a function here, but just calling from
// scene doesn't work so we do it like this
void Render() { scene.Render(); }

void Render(int n)
{
    float currentFrame = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Final Nick de Bruin s1141131");

    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyboardHandler);
    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glewInit();

    scene = MainScene(WIDTH, HEIGHT);

    ShowWindow(
        GetConsoleWindow(),
        SW_HIDE
    );

    glutMainLoop();

    return 0;
}
