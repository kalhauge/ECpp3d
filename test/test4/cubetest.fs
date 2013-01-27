#version 150
out vec4 stdout;
uniform samplerCube uColorTex;
in vec3 position;

void main(void)
{
    stdout = texture(uColorTex,position.xyz);
}
