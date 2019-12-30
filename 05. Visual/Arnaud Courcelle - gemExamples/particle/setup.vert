
varying vec2 vUv;

void main(void) {
	vUv = gl_MultiTexCoord0.st;
	gl_Position = ftransform();
}