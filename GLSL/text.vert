#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uva;

uniform mat4 projection;
uniform mat4 view;
out vec2 uvaPos;

void main()
{
    uvaPos = uva;
    gl_Position = projection * vec4(aPos, 1.0);
}
