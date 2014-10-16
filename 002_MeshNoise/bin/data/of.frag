#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

void main(){
	// vec3 v = gl_Vertex.xyz;
	// vec3 c = vec3(sin(v.x), 0.0, 0.0);
	gl_FragColor = gl_Color;
	// gl_FragColor = vec4(c, 1.0);
}
