#version 460 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 textureCoords;

out vec3 Normals;
out vec2 TextureCoords;

uniform mat4
    projection,
    view,
    model;

void main(){
    gl_Position = projection * view * model * vec4(positions, 1.0);
}