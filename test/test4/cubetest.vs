#version 150
uniform mat4 mvpMatrix;
in vec4 vPosition;
out vec3 position;

void main()
{
    gl_Position = mvpMatrix * vPosition;
    position = vPosition.xyz / vPosition.w; 
}
