/*
  Daily an hour GLSL sketch by @chimanaco 21/30

  Reference:
  http://www.demoscene.jp/?p=1147
*/ 

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 resolution;
uniform float time;

float lengthN(vec2 v, float n)
{
  vec2 tmp = pow(abs(v), vec2(n));
  return pow(tmp.x + tmp.y, 1.0/n);
}

float rings(vec2 p)
{
  vec2 p2 = mod(p * 8.0, 8.0)- 4.0;
  return sin(lengthN(p2, 4.0)* 16.0 + time * 10. );
}

vec2 trans(vec2 p)
{
  return vec2(p.x + sin(p.y * 10.)*0.3, p.y + sin(p.x * 10. + time) * 0.3);
}

void main( void ) {
  vec2 pos = (gl_FragCoord.xy*2.0 -resolution) / resolution.y;
  gl_FragColor = vec4(0.0, rings(trans(pos)), 0.0, 1.0);
}
