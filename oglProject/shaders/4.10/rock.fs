#version 460 core

in vec2 fTexCoords;
out vec4 FragColor;

struct Material{
  	sampler2D texture_diffuse1;
};
uniform Material material;

void main(){
    FragColor = texture(material.texture_diffuse1, fTexCoords);
}