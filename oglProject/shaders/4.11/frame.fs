#version 460 core

in vec2 fTextureCoords;

out vec4 FragColor;

uniform sampler2D inTexture;

void main(){
    FragColor = texture(inTexture, fTextureCoords);
}