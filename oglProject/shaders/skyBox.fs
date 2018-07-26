#version 460 core

out vec4 color;
in vec3 texCoords;
uniform samplerCube inTexture;

void main(){
    color = texture(inTexture, texCoords);
}