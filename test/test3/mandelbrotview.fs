#version 150
out vec4 stdout;
in  vec4 position;

uniform mat4 uPosToCoord;
uniform sampler1D uColorTex;
uniform sampler2D uZvalues;
uniform float uIteration;

void main(void) {
	float iteration  = texture(uZvalues,(uPosToCoord * position).xy).z;
	if(iteration >= uIteration - 0.5f) {
		stdout = vec4(0,0,0,1);
	} else {
		stdout = texture(uColorTex,sin(iteration / 50.0));
	}
}
