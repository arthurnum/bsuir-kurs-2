#version 330 core

uniform mat4 model;

in vec3 normal;
out vec4 FragColor;

void main()
{
   vec3 light = normalize( vec3(sin(0.25), cos(0.5), -cos(0.25)) );
   float cosTheta = clamp(
      dot( normal, light ),
      0.5,
      1.0
   );
   vec3 result = vec3(1.0, 0.85, 0.85) * cosTheta;
   FragColor = vec4(result, 1.0);
}
