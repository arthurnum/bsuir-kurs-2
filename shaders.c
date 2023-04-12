#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shaders.h"

char* loadShaderSource(const char* filename) {
    FILE *f;
    long size = 0;
    char* source;

    // Read File to get size
    f = fopen(filename, "rb");
    if  (!f) {
        printf("Can not open %s\n", filename);
        return "";
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f) + 1;
    fclose(f);

    // Read File
    f = fopen(filename, "r");
    source = memset(malloc(size), '\0', size);
    fread(source, 1, size - 1, f);
    fclose(f);

    return source;
}

Shader loadVertexShader(const char* filename) {
    Shader shader;
    shader = glCreateShader(GL_VERTEX_SHADER);

    char* source = loadShaderSource(filename);
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);
    free(source);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    };

    return shader;
}

Shader loadFragmentShader(const char* filename) {
    Shader shader;
    shader = glCreateShader(GL_FRAGMENT_SHADER);

    char* source = loadShaderSource(filename);
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);
    free(source);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    };

    return shader;
}

ShaderProgram buildShaderProgram(Shader vertex, Shader fragment) {
    ShaderProgram program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    return program;
}

void uniformMatrix(ShaderProgram program, const char* name, float* matrix) {
    unsigned int location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_TRUE, matrix);
}

void uniformSampler2D(ShaderProgram program, const char* name, unsigned int id) {
    unsigned int location = glGetUniformLocation(program, name);
    glUniform1i(location, id);
}
