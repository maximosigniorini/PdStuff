const vec2 canvasSize=vec2(1000.,1000.);
uniform sampler2D texture;
uniform float ran;
uniform vec2 mouse;
uniform bool mouseDown;

uniform bool isProp;
uniform bool isInverse;

uniform float maxSpeed;
uniform float reduceSpeed;
uniform float radius;
uniform float strength;
uniform float areaVariable;

uniform float screw;
uniform bool bothSides;
uniform float screwVariable;

const float PI = 3.14159265359;
const float UNIT = 10000.0;

float rand(vec2 p){
    return fract(sin(dot(p ,vec2(12.9898,78.233))) * 43758.5453);
}
vec2 rotate(vec2 vec, float rad) {
    mat2 mat = mat2(
    	cos(rad), -sin(rad),
    	sin(rad), cos(rad)
    );
    return mat * vec;
}



varying vec2 vUv;

void main(void) {

	vec4 node = (texture2D(texture, vUv) * 2.0 - 1.0) * UNIT;

	vec2 dxy = node.xy - mouse*canvasSize;
	vec2 nxy = normalize(dxy);
	float len = length(dxy);
	float r = rand(vUv);
	float area = (r * areaVariable + (1.0 - areaVariable)) * radius;
	if (mouseDown && len < area) {
		if (!isProp) {
			len = area;
		} else {
			if (isInverse) len = area - len;
		}

		float sign = 1.0;
		if (bothSides) {
			if (mod(fract(r * UNIT), 2.0) > 0.5) sign = -1.0;
		}
		float rot = screw * sign * (r * screwVariable + (1.0 - screwVariable));
		node.zw -= rotate(nxy * len * strength, rot);
	}

	len = length(node.zw);
	if (len > maxSpeed) {
		node.zw *= reduceSpeed;
	}

	node.xy += node.zw;
	if (node.x > canvasSize.x) {
		node.x = canvasSize.x;
		node.z *= -1.0;
	} else if (node.x < -canvasSize.x) {
		node.x = -canvasSize.x;
		node.z *= -1.0;
	}
	if (node.y > canvasSize.y) {
		node.y = canvasSize.y;
		node.w *= -1.0;
	} else if (node.y < -canvasSize.y) {
		node.y = -canvasSize.y;
		node.w *= -1.0;
	}

	node = node / UNIT / 2.0 + 0.5;
	gl_FragColor = node;
}
