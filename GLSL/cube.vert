#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec4 normal;

void main()
{
    normal = model * vec4(aNormal, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
