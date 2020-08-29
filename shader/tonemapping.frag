#version 330 core

in vec2 uv;

out vec4 fragColor;

uniform float gamma = 2.2;
uniform float tonemappingEnabled;
uniform sampler2D texture0;
uniform vec2 resolution;

///----
/// Narkowicz 2015, "ACES Filmic Tone Mapping Curve"
vec3 aces(vec3 x) {
  const float a = 2.51;
  const float b = 0.03;
  const float c = 2.43;
  const float d = 0.59;
  const float e = 0.14;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

float aces(float x) {
  const float a = 2.51;
  const float b = 0.03;
  const float c = 2.43;
  const float d = 0.59;
  const float e = 0.14;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}
///----

void main() {
  fragColor = texture(texture0, uv);

  if (tonemappingEnabled > 0.5) {
    // ACES filmic tone mapping
    fragColor.rgb = aces(fragColor.rgb);

    // Gamma correction
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / gamma));
  }
}