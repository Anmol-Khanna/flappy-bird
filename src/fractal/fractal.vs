#version 410 core
layout(location = 0) in vec2 pos;
uniform mat4 viewProjection;

void main() { gl_Position = viewProjection * vec4(pos, -1.0, 1.0); }
