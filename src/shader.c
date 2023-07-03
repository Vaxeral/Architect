#include "shader.h"

Shader shaderCreate(GLchar *vertexShaderSource, GLint vertexShaderSourceLength, GLchar *fragmentShaderSource, GLint fragmentShaderSourceLength)
{
    Shader shader;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLint success;
    GLchar *infoLog;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, &vertexShaderSourceLength);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, &fragmentShaderSourceLength);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }

    shader.id = glCreateProgram();
    glAttachShader(shader.id, vertexShader);
    glAttachShader(shader.id, fragmentShader);
    glLinkProgram(shader.id);
    glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader.id, sizeof infoLog / sizeof *infoLog, NULL, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}
void shaderUse(Shader *shader)
{
    glUseProgram(shader->id);
}
void shaderSetFloat(Shader *shader, GLchar *uniform, GLfloat value)
{
    glUniform1f(glGetUniformLocation(shader->id, uniform), value);
}
void shaderSetInteger(Shader *shader, GLchar *uniform, GLint value)
{
    glUniform1i(glGetUniformLocation(shader->id, uniform), value);
}
void shaderSetVector2f(Shader *shader, GLchar *uniform, GLfloat *vector)
{
    glUniform2fv(glGetUniformLocation(shader->id, uniform), 1, vector);
}
void shaderSetVector3f(Shader *shader, GLchar *uniform, GLfloat *vector)
{
    glUniform3fv(glGetUniformLocation(shader->id, uniform), 1, vector);
}
void shaderSetVector4f(Shader *shader, GLchar *uniform, GLfloat *vector)
{
    glUniform4fv(glGetUniformLocation(shader->id, uniform), 1, vector);
}
void shaderSetMatrix4(Shader *shader, GLchar *uniform, GLfloat *matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->id, uniform), 1, 0, matrix);
}