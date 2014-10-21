uniform sampler2DRect texture0;
uniform float time;
uniform float w;
uniform float h;


varying vec2 v;

void main(){
	//Getting coordinates of the current pixel in texture
	vec2 pos = gl_TexCoord[0].xy;	// gl_FragCoord
	
	// 0 - 1
	vec2 p = vec2(pos.x / w, pos.y / h);

 	// if(p.y < 1.0) {
	// p.x = abs(p.x - 0.5) + 0.5;
	// p.x = 0.5;
	// p.x = fract(time*.01);
	// p.x = p.x + sin(p.y*80.)*0.01;
	p.x = p.x + sin(p.y * 80. * cos(time * 0.37) + time * 3.) * 0.1 * sin(time);
	// p = fract(p * 6.);
	// pos.y = abs(pos.y - 400.) + 400.;
 	// } else {
 		// pos.x = sin( - pos.x);
 	// }

 	pos = vec2(p.x * w, p.y * h);

 	vec4 color = texture2DRect(texture0, pos);
 	gl_FragColor = color;
}
