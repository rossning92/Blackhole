#version 330 core

layout(location = 0) in vec3 position;

out vec2 uv;

void main() {
  uv = (position.xy + 1.0) * 0.5;
  gl_Position = vec4(position, 1.0);
}