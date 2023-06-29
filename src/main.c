#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

GLchar vertexShaderSource[] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x34, 0x36, 0x30,
    0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6c, 0x61, 0x79, 0x6f, 0x75, 0x74,
    0x20, 0x28, 0x6c, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d,
    0x20, 0x30, 0x29, 0x20, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20,
    0x61, 0x50, 0x6f, 0x73, 0x3b, 0x0a, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20,
    0x6d, 0x61, 0x69, 0x6e, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e,
    0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x61, 0x50, 0x6f, 0x73,
    0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x0a
};

GLint vertexShaderSourceLength = sizeof vertexShaderSource / sizeof *vertexShaderSource;

GLchar fragmentShaderSource[] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x34, 0x36, 0x30,
    0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6f, 0x75, 0x74, 0x20, 0x76, 0x65,
    0x63, 0x34, 0x20, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72,
    0x3b, 0x0a, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e,
    0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x46, 0x72, 0x61,
    0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x76, 0x65, 0x63,
    0x34, 0x28, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x35, 0x2c, 0x20,
    0x30, 0x2e, 0x32, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x7d,
    0x0a
};

GLint fragmentShaderSourceLength = sizeof fragmentShaderSource / sizeof *fragmentShaderSource;

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
    char *p;

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
    p = vertexShaderSource;
    glShaderSource(vertexShader, 1, &p, &vertexShaderSourceLength);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    p = fragmentShaderSource;
    glShaderSource(fragmentShader, 1, &p, &fragmentShaderSourceLength);
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
