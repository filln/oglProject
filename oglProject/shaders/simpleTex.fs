#version 460 core

in vec2 TexCoords;

out vec4 outColor;
uniform sampler2D inTexture;
void main(){
	outColor = texture(inTexture, TexCoords);
}






























































