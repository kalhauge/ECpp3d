#version 150
uniform mat4 mvpMatrix;

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

void main()
{
    gl_Position = mvpMatrix * vPosition;
    color = vColor;
}
