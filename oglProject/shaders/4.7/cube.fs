#version 460 core

in vec3 Normals;
in vec2 TextureCoords;

out vec4 color;

void main(){
    color = vec4(Normals, 1.0) + vec4(TextureCoords, 1.0, 1.0);
}