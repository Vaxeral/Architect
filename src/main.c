#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#error Write tool that outputs an embedable C string from a file using hexadecimal escape sequences.

char *vertexShaderSource = "\
\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x34\x36\x30\
\x20\x63\x6f\x72\x65\x0a\x6c\x61\x79\x6f\x75\x74\
\x20\x28\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x3d\
\x20\x30\x29\x20\x69\x6e\x20\x76\x65\x63\x33\x20\
\x61\x50\x6f\x73\x3b\x0a\x0a\x76\x6f\x69\x64\x20\
\x6d\x61\x69\x6e\x28\x29\x0a\x7b\x0a\x20\x20\x20\
\x20\x67\x6c\x5f\x50\x6f\x73\x69\x74\x69\x6f\x6e\
\x20\x3d\x20\x76\x65\x63\x34\x28\x61\x50\x6f\x73\
\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x7d\x0a\x00";


char *fragmentShaderSource = "\
\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x34\x36\x30\
\x20\x63\x6f\x72\x65\x0a\x6f\x75\x74\x20\x76\x65\
\x63\x34\x20\x46\x72\x61\x67\x43\x6f\x6c\x6f\x72\
\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\
\x28\x29\x0a\x7b\x0a\x20\x20\x20\x20\x46\x72\x61\
\x67\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x76\x65\x63\
\x34\x28\x31\x2e\x30\x2c\x20\x30\x2e\x35\x2c\x20\
\x30\x2e\x32\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x7d\
\x0a\x00";

void myGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);
void myGlfwErrorCallback(int error, const char *description);

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    float vertices[] = { -0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0 };
    GLuint vertexBufferObject;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vertexArrayObject;
    int success;
    char infoLog[512];

    glfwSetErrorCallback(myGlfwErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Architect", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, myGlfwFramebufferSizeCallback);
    glfwSwapInterval(0);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof *vertices, (void *)0);
    glEnableVertexAttribArray(0);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void myGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void myGlfwErrorCallback(int error, const char *description)
{
    fprintf(stderr, "%s\n", description);
    exit(EXIT_FAILURE);
}
