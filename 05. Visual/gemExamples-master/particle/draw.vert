
const float UNIT = 10000.0;
const float cs=100.;


uniform sampler2D texture;
uniform float size;
uniform float ptSize;
uniform vec2 canvasSize;

varying vec4 vColor;

void main(void) {
	float aIndex=gl_Vertex.x;
	if(aIndex>size*size){return;}
	vec2 pos=vec2(mod(aIndex,size),floor(aIndex/size))/size;
	vec2 uv = vec2((mod(aIndex, size) ) / size, (floor(aIndex / size) ) / size);
	vec2 node = texture2D(texture, pos).xy ;
	node *= cs;
	node-=cs/2.;

	vColor = vec4( 0.9);
	gl_Position = gl_ModelViewProjectionMatrix*vec4(node,0.,1.);;
	gl_PointSize = ptSize;
}