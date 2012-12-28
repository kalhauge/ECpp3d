#version 150
out vec4 stdout;
uniform sampler2D uColorTex;
in vec2 tex;

void main(void)
{
    stdout =texture(uColorTex,tex);
}
