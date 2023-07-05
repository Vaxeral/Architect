#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"
#include "camera.h"

GLchar vertexShaderSource[] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x34, 0x36, 0x30,
    0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6c, 0x61, 0x79, 0x6f, 0x75, 0x74,
    0x20, 0x28, 0x6c, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d,
    0x20, 0x30, 0x29, 0x20, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20,
    0x61, 0x50, 0x6f, 0x73, 0x3b, 0x0a, 0x6c, 0x61, 0x79, 0x6f, 0x75, 0x74,
    0x20, 0x28, 0x6c, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d,
    0x20, 0x31, 0x29, 0x20, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20,
    0x61, 0x54, 0x65, 0x78, 0x3b, 0x0a, 0x0a, 0x6f, 0x75, 0x74, 0x20, 0x76,
    0x65, 0x63, 0x32, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x50,
    0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x0a, 0x75, 0x6e,
    0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x6d,
    0x6f, 0x64, 0x65, 0x6c, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72,
    0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x76, 0x69, 0x65, 0x77, 0x3b,
    0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74,
    0x34, 0x20, 0x70, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e,
    0x3b, 0x0a, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e,
    0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78,
    0x74, 0x75, 0x72, 0x65, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e,
    0x20, 0x3d, 0x20, 0x61, 0x54, 0x65, 0x78, 0x3b, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e,
    0x20, 0x3d, 0x20, 0x70, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x6f,
    0x6e, 0x20, 0x2a, 0x20, 0x76, 0x69, 0x65, 0x77, 0x20, 0x2a, 0x20, 0x6d,
    0x6f, 0x64, 0x65, 0x6c, 0x20, 0x2a, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28,
    0x61, 0x50, 0x6f, 0x73, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a,
    0x7d, 0x0a
};

GLint vertexShaderSourceLength = sizeof vertexShaderSource / sizeof *vertexShaderSource;

GLchar fragmentShaderSource[] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x34, 0x36, 0x30,
    0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6f, 0x75, 0x74, 0x20, 0x76, 0x65,
    0x63, 0x34, 0x20, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72,
    0x3b, 0x0a, 0x0a, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x74,
    0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69,
    0x6f, 0x6e, 0x3b, 0x0a, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d,
    0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x74,
    0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x31, 0x3b, 0x0a, 0x0a, 0x76, 0x6f,
    0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x28, 0x29, 0x0a, 0x7b, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f,
    0x72, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28,
    0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x31, 0x2c, 0x20, 0x74, 0x65,
    0x78, 0x74, 0x75, 0x72, 0x65, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f,
    0x6e, 0x29, 0x3b, 0x0a, 0x7d, 0x0a
};

GLint fragmentShaderSourceLength = sizeof fragmentShaderSource / sizeof *fragmentShaderSource;

void myGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);
void myGlfwErrorCallback(int error, const char *description);
void myGlfwMouseCallback(GLFWwindow *window, double xposIn, double yposIn);

mat4 projection;
mat4 model;
mat4 view;

Camera camera;
float lastX = 640.0 / 2.0;
float lastY = 480.0 / 2.0;
int firstMouse = 1;

float deltaTime;
float lastFrame;

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    // GLfloat vertices[] = {
    //     0.0, 0.0, 0.0, 0.0, 0.0,
    //     0.0, 0.0, 0.0, 1.0, 1.0,
    //     0.0, 0.0, 0.0, 1.0, 0.0,

    //     0.0, 0.0, 1.0, 1.0, 0.0,
    //     0.0, 0.0, 1.0, 1.0, 0.0,
    //     0.0, 0.0, 1.0, 0.0, 0.0,
    
    //     0.0, 1.0, 0.0, 0.0, 1.0,
    //     0.0, 1.0, 0.0, 0.0, 1.0,
    //     0.0, 1.0, 0.0, 1.0, 1.0,
    
    //     0.0, 1.0, 1.0, 1.0, 1.0,
    //     0.0, 1.0, 1.0, 0.0, 0.0,
    //     0.0, 1.0, 1.0, 0.0, 1.0,
    
    //     1.0, 0.0, 0.0, 0.0, 1.0,
    //     1.0, 0.0, 0.0, 1.0, 0.0,
    //     1.0, 0.0, 0.0, 0.0, 0.0,
    
    //     1.0, 0.0, 1.0, 0.0, 0.0,
    //     1.0, 0.0, 1.0, 1.0, 0.0,
    //     1.0, 0.0, 1.0, 0.0, 0.0,
    
    //     1.0, 1.0, 0.0, 1.0, 1.0,
    //     1.0, 1.0, 0.0, 1.0, 1.0,
    //     1.0, 1.0, 0.0, 0.0, 1.0,
    
    //     1.0, 1.0, 1.0, 1.0, 0.0,
    //     1.0, 1.0, 1.0, 1.0, 1.0,
    //     1.0, 1.0, 1.0, 0.0, 1.0,
    // };
    // GLuint indices[] = {
    //     0 * 3 + 0, 3 * 3 + 0, 2 * 3 + 0,
    //     3 * 3 + 0, 0 * 3 + 0, 1 * 3 + 0,

    //     1 * 3 + 1, 4 * 3 + 0, 5 * 3 + 0,
    //     4 * 3 + 0, 1 * 3 + 1, 0 * 3 + 1,
        
    //     2 * 3 + 1, 7 * 3 + 0, 6 * 3 + 0,
    //     7 * 3 + 0, 2 * 3 + 1, 3 * 3 + 1,
        
    //     3 * 3 + 2, 5 * 3 + 1, 7 * 3 + 1,
    //     5 * 3 + 1, 3 * 3 + 2, 1 * 3 + 2,
        
    //     5 * 3 + 2, 6 * 3 + 1, 7 * 3 + 2,
    //     6 * 3 + 1, 5 * 3 + 2, 4 * 3 + 1,
        
    //     6 * 3 + 2, 0 * 3 + 2, 2 * 3 + 2,
    //     0 * 3 + 2, 6 * 3 + 2, 4 * 3 + 2,
    // };

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7
 
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15
 
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
        0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
    };
    // index data
    GLuint indices[] = {
        // front and back
        0, 3, 2,
        2, 1, 0,
        4, 5, 6,
        6, 7 ,4,
        // left and right
        11, 8, 9,
        9, 10, 11,
        12, 13, 14,
        14, 15, 12,
        // bottom and top
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };

    GLuint vertexBufferObject;
    Shader shader;
    GLuint vertexArrayObject;
    GLint success;
    GLchar infoLog[512];
    GLchar *p;
    GLint vertexColorLocation;
    GLuint texture;
    GLuint elementBufferObject;
    int width;
    int height;
    int nrChannels;
    unsigned char *data;

    camera = cameraCreate((vec3){0.0, 0.0, 2.0}, -90.0, 0.0);

    glm_mat4_copy(GLM_MAT4_IDENTITY, projection);
    glm_mat4_copy(GLM_MAT4_IDENTITY, model);
    glm_mat4_copy(GLM_MAT4_IDENTITY, view);

    glm_translate(view, (vec3){0.0, 0.0, -2.0});
    glm_perspective(M_PI * 2.0 / 8.0, 640.0 / 480.0, 0.1, 100.0, projection);

    glfwSetErrorCallback(myGlfwErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Architect", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, myGlfwFramebufferSizeCallback);
    glfwSetCursorPosCallback(window, myGlfwMouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(0);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    shader = shaderCreate(vertexShaderSource, vertexShaderSourceLength, fragmentShaderSource, fragmentShaderSourceLength);
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof *vertices, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof *vertices, (void *)(3 * sizeof *vertices));
    glEnableVertexAttribArray(1);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(1);
    data = stbi_load("assets/awesomeface.png", &width, &height, &nrChannels, 0);
    assert(data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    shaderUse(&shader);
    shaderSetInteger(&shader, "texture1", 0);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, 1);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraProcessKeyboard(&camera, FORWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraProcessKeyboard(&camera, BACKWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraProcessKeyboard(&camera, LEFT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraProcessKeyboard(&camera, RIGHT, deltaTime);
        }

        glfwPollEvents();
        glClearColor(1.0, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderUse(&shader);
        shaderSetMatrix4(&shader, "model", (float *)model);
        cameraGetViewMatrix(&camera, view);
        shaderSetMatrix4(&shader, "view", (float *)view);
        shaderSetMatrix4(&shader, "projection", (float *)projection);
        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
void myGlfwFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glm_perspective(M_PI * 2.0 / 8.0, (float)width / (float)height, 0.1, 100.0, projection);
}
void myGlfwErrorCallback(int error, const char *description)
{
    fprintf(stderr, "%s\n", description);
    exit(EXIT_FAILURE);
}
void myGlfwMouseCallback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = (float)xposIn;
    float ypos = (float)yposIn;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    cameraProcessMouseMovement(&camera, xoffset, yoffset);
}
