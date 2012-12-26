#version 150
uniform mat4 mvpMatrix;

in vec4 vPosition;
in vec2 vTexCoord1;
out vec2 tex;

void main()
{
    gl_Position = mvpMatrix * vPosition;
    tex = vTexCoord1;
}
