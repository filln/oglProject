#version 460 core

in vec2 TexCoords;

out vec4 outColor;
struct Material{
  	sampler2D texture_diffuse1;
};
uniform Material material;
void main(){
	vec4 texture = texture(material.texture_diffuse1, TexCoords);
	if(texture.a < 0.49) discard;
	outColor = texture;
}






























































