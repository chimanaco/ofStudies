varying vec3 v;

uniform sampler2D tex;

void main (void) {
    vec3 p = v.xyz;

    gl_FragColor = texture2D(tex, gl_TexCoord[0].st) * gl_Color * vec4(cos(p.z), tan(p.x), cos(p.y), 1.0);
    // gl_FragColor = texture2D(tex, gl_TexCoord[0].st) * gl_Color;
    // gl_FragColor = vec4(vec3(p.x), 1.0);
}