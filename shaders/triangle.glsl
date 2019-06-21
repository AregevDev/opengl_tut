#shader vertex
#version 150 core

in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.xyz, 1.0);
}

#shader fragment
#version 150 core

out vec4 color;

uniform vec4 u_color;

void main() {
    color = u_color;
}