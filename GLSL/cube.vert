#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec3 normal;

void main()
{
    vec3 buf = vec3(model * vec4(aNormal, 0.0));
    normal = normalize(buf);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
