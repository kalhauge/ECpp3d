#version 150
out vec4 fragColor;
uniform sampler2D uColorTex;
in vec3 position;

void main(void)
{
    fragColor = texture(uColorTex,position.xy);
}
