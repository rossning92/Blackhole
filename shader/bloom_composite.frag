#version 330 core

in vec2 uv;

out vec4 fragColor;

uniform float tone = 1.0;
uniform float bloomStrength = 0.1;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec2 resolution; // viewport resolution in pixels

void main() {
  fragColor =
      texture(texture0, uv) * tone + texture(texture1, uv) * bloomStrength;
}