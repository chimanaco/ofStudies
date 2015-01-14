uniform float t;

varying vec2 vUv;
varying float time;
varying vec3 position;

void main() {
	time = t;
	position = gl_Vertex.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	// position.x *= sin(t);
	// gl_Position = gl_ModelViewProjectionMatrix *vec4( position, 1.0 );;
	// gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}




