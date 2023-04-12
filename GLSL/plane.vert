#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * mat4(1.0) * vec4(aPos, 1.0);
}
