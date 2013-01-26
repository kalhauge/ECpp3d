#version 150

out vec4 stdout;

in vec4 position;

uniform mat4 uPosToCoord;
uniform sampler2D uZvalues;

vec2 complexmult(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y* b.y, (a.x+a.y)*(b.x + b.y) - a.x * b.x - a.y * b.y);
}

void main(void) {
	vec2 number = texture(uZvalues,(uPosToCoord * position).xy).xy;
	float iteration = texture(uZvalues,(uPosToCoord * position).xy).z;
	if(dot(number,number) < 4) {
		iteration = iteration +1;
		number = complexmult(number,number) + position.xy;
	}
	stdout = vec4(number,iteration,1);
}
