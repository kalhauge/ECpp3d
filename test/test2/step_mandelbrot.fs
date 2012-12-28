#version 150
out vec4 out0;
out vec2 out1;
out int out2;
in  vec2  position;

uniform sampler1D uColorTex;
uniform int iteration;
uniform int limit;

vec2 complexmult(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y* b.y, (a.x+a.y)*(b.x + b.y) - a.x * b.x - a.y * b.y);
}

void main(void) {
	vec2 number;
	out0 = texture(uColorTex,float(iteration)/limit);
	out1 = number;
}
