#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>

void MyGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);
void MyGlfwErrorCallback(int error, const char *description);

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    glfwSetErrorCallback(MyGlfwErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Architect", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, MyGlfwFramebufferSizeCallback);
    glfwSwapInterval(0);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    return 0;
}

void MyGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void MyGlfwErrorCallback(int error, const char *description)
{
    fprintf(stderr, "%s\n", description);
}
