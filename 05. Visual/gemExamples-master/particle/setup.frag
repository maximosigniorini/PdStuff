//precision mediump float;

const float UNIT = 10000.0;

const float PI = 3.14159265359;

float rand(vec2 p){
    return fract(sin(dot(p ,vec2(12.9898,78.233))) * 43758.5453);
}

uniform float ran;
uniform float size;

varying vec2 vUv;

void main(void){
	float i = vUv.x * size + vUv.y;
	float rad = i * PI;

	float px = rand(vUv * ran * 2.0) * 2.0 - 1.0;
	float py = rand(vUv * ran * 4.0) * 2.0 - 1.0;
	px = px * 100.0 / UNIT * cos(rad);
	py = py * 100.0 / UNIT * sin(rad);
	px = px / 2.0 + 0.5;
	py = py / 2.0 + 0.5;

	float vx = rand(vUv * ran * 8.0) * 2.0 - 1.0;
	float vy = rand(vUv * ran * 16.0) * 2.0 - 1.0;
	vx = vx * 10.0 / UNIT * cos(rad);
	vy = vy * 10.0 / UNIT * sin(rad);
	vx = vx / 2.0 + 0.5;
	vy = vy / 2.0 + 0.5;

	gl_FragColor = vec4(px, py, vx, vy);
}