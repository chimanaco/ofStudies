varying vec3 v;

void main() {
	v = gl_Vertex.xyz;

    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
	float size    = gl_Normal.y	;
    gl_PointSize  = size;
    gl_FrontColor = gl_Color;

}