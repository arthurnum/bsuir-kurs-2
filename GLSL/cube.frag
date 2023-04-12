#version 330 core

in vec4 normal;
out vec4 FragColor;

void main()
{
   float cosTheta = clamp( dot( normal, normalize(vec4(-5.0, 15.0, -10.0, 1.0)) ), 0.5, 1.0);
   vec3 result = vec3(0.8, 0.8, 0.8) * cosTheta;
   FragColor = vec4(result, 1.0);
}
