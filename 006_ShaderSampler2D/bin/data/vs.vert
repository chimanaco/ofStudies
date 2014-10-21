varying vec2 v;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	v = gl_Vertex.xy;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
}
