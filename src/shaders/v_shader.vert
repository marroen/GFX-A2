#version 330 core

layout(location = 0) in vec3 inPosition;   // Vertex position
layout(location = 1) in vec3 inColor;      // Vertex color

out vec3 fragColor;

void main() {
    fragColor = inColor;
    gl_Position = vec4(inPosition, 1.0);
}
