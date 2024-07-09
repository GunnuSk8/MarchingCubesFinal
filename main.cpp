#include <GLFW/glfw3.h>
#include "MarchingCubes.h"
static void MC() {
    static float cRot = 20;
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glRotatef(cRot, 1.0, 1.0, 0.0);
    DrawBoundingBox3D();
    GridIntensityUpdate();
    MarchingCubes();

    cRot += 0;
    glPopMatrix();
    glFlush();
}
int main(void)
{
    GLFWwindow* window;
    GridInit();
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    float screenSize = 2;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480 * screenSize, 480 * screenSize, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        MC();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}