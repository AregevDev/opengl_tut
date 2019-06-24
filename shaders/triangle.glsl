#shader vertex
#version 150 core

in vec3 aPos;
in vec2 texCoord;

out vec2 v_texCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    v_texCoord = texCoord;
}

#shader fragment
#version 150 core

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

out vec4 color;

void main() {
    vec4 texColor = texture(u_texture, v_texCoord);
    color = texColor;
}
