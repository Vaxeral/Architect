#ifndef ARCHITECT_SHADER_H
#define ARCHITECT_SHADER_H

#include <glad/glad.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Shader
{
    GLuint id;
}
Shader;

Shader shaderCreate(GLchar *vertexShaderSource, GLint vertexShaderSourceLength, GLchar *fragmentShaderSource, GLint fragmentShaderSourceLength);
void shaderUse(Shader *shader);
void shaderSetBool(Shader *shader, GLchar *uniform, GLboolean value);
void shaderSetInt(Shader *shader, GLchar *uniform, GLint value);
void shaderSetFloat(Shader *shader, GLchar *uniform, GLfloat value);

#endif
