#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

out vec2 fTextureCoords;

void main(){
    fTextureCoords = textureCoords;
    gl_Position = vec4(position, 0.0, 1.0);
}