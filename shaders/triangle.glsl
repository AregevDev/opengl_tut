#shader vertex
#version 150 core

in vec4 aPos;
in vec2 texCoord;

out vec2 v_texCoord;
uniform mat4 u_mvp;

void main() {
    gl_Position = u_mvp * aPos;
    v_texCoord = texCoord;
}

#shader fragment
#version 150 core

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

out vec4 color;

void main() {
    vec4 tex_color = texture(u_texture, v_texCoord);
    color = tex_color * u_color;
}
