#version 150 core

in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.xyz, 1.0);
}