#version 150
out vec4 fragColor;
uniform sampler1D uColorTex;
in vec3 position;

void main(void)
{
    fragColor = texture(uColorTex,length(position));
}
