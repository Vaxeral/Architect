#ifndef SHADER_H
#define SHADER_H

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
void shaderSetFloat(Shader *shader, GLchar *uniform, GLfloat value);
void shaderSetInteger(Shader *shader, GLchar *uniform, GLint value);
void shaderSetVector2f(Shader *shader, GLchar *uniform, GLfloat *vector);
void shaderSetVector3f(Shader *shader, GLchar *uniform, GLfloat *vector);
void shaderSetVector4f(Shader *shader, GLchar *uniform, GLfloat *vector);
void shaderSetMatrix4(Shader *shader, GLchar *uniform, GLfloat *matrix);

#endif
