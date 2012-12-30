#version 150
#extension GL_ARB_gpu_shader_fp64 : enable

in  vec4 vPosition;

out vec4  position;

uniform mat4 mvpMatrix;

void main() {
	gl_Position = vPosition;
	position = (mvpMatrix * vPosition);
}
