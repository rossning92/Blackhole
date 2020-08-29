#version 330 core

out vec4 fragColor;

uniform vec2 resolution;
uniform sampler2D texture0;

void main() {
  vec2 uv = gl_FragCoord.xy / resolution;
  fragColor = texture(texture0, uv);
}