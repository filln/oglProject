#version 460 core

in GS_OUT{
	vec2 texCoords;
} fs_in;
out vec4 FragColor;

struct Material{
	sampler2D 
		texture_diffuse1,
		texture_specular1;
};
uniform Material material;

void main(){
	vec3 textureColor = vec3(texture(material.texture_diffuse1, fs_in.texCoords));
	FragColor = vec4(textureColor, 1.0f);
}































































