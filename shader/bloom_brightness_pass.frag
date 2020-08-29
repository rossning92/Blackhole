#version 330 core

uniform sampler2D texture0;
uniform vec2 resolution; // viewport resolution in pixels

const float brightPassThreshold = 1.0;
const vec3 luminanceVector = vec3(0.2125, 0.7154, 0.0721);

void main() {
  vec2 texCoord = gl_FragCoord.xy / resolution.xy;

  vec4 c = texture2D(texture0, texCoord);

  float luminance = dot(luminanceVector, c.xyz);
  luminance = max(0.0, luminance - brightPassThreshold);
  c.xyz *= sign(luminance);
  c.a = 1.0;

  gl_FragColor = c;
}