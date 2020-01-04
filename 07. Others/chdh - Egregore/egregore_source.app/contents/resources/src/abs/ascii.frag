// Cyrille Henry 2007

uniform float letter_ascii, color;
uniform sampler2D tex0;
float nb_line = 16.;
float nb_col = 16.;
void main()
{
	vec2 pos =  (gl_TextureMatrix[0] * gl_TexCoord[0]).st;
	float col = mod(letter_ascii,nb_col);
	float line = floor(letter_ascii/nb_col);
	pos.s = pos.s/(nb_col-0.) + col/nb_col;
	pos.t = pos.t/(nb_line-0.) + line/nb_line;
	gl_FragColor = texture2D(tex0, pos) * color ;
}










