typedef unsigned int Shader;
typedef unsigned int ShaderProgram;

Shader loadVertexShader(const char* filename);
Shader loadFragmentShader(const char* filename);
ShaderProgram buildShaderProgram(Shader vertex, Shader fragment);
void uniformMatrix(ShaderProgram program, const char* name, float* matrix);
void uniformSampler2D(ShaderProgram program, const char* name, unsigned int id);
