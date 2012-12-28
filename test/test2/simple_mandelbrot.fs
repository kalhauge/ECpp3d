#version 150
out vec4 out0;
in  vec2  position;

uniform sampler1D uColorTex; 
uniform int limit;

vec2 complexmult(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y* b.y, (a.x+a.y)*(b.x + b.y) - a.x * b.x - a.y * b.y);
}

void main(void) {
	vec2 number = vec2(0,0);
	int itr = 0;
	for(itr = 0; itr < limit; ++itr) {
		number = complexmult(number,number) + position;
		if(length(number) > 2) {
			break;
		}
	}
	out0 = texture(uColorTex,float(itr)/limit);
}
