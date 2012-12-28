#version 150

in  vec4 vPosition;
out vec2  position;
uniform mat4 mvpMatrix;

void main() {
	gl_Position = vPosition;
	position = (mvpMatrix * vPosition).xy;
}
