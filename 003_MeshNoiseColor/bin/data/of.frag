#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

varying vec3 v3;
varying float depth;

vec3 hsv2rgb(vec3 c){
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main(){
	vec3 pos = v3.xyz;
	// float z = clamp(pos.z, 0.0, 1.0);
	//vec3 c = vec3( pos.z / 100, 1.0, 1.0);

	vec3 c = hsv2rgb( vec3(pos.z / depth, 0.3, 0.4));

	// gl_FragColor = gl_Color;
	gl_FragColor = vec4(c, 1.0);
	// gl_FragColor = vec4(c, 1.0);
}
