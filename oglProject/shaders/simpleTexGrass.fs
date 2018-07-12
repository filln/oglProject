#version 460 core

in vec2 TexCoords;

out vec4 outColor;
uniform sampler2D inTexture;
void main(){
	vec4 texture = texture(inTexture, TexCoords);
	if(texture.a < 0.49) discard;
	outColor = texture;
}






























































