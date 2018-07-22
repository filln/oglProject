#version 460 core

in vec2 texCoords;
out vec4 outColor;
uniform sampler2D inTexture;

void main(){
    outColor = texture(inTexture, texCoords);
}