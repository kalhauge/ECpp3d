#version 150
out vec4 fragColor;
uniform sampler2D uColorTex;
in vec2 tex;

void main(void)
{
    fragColor =texture(uColorTex,tex);
}
