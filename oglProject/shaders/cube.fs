#version 460 core

in vec3 
	Normal, FragPos;

struct Material{
vec3 
	ambient,
	diffuse,
	specular;
float shininess;
};
struct Light{
vec3 
	position,
	ambient,
	diffuse,
	specular;
};
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 color;

void main(){

vec3 
	norm = normalize(Normal),
	lightDir = normalize(light.position - FragPos),
	viewDir = normalize(viewPos - FragPos),
	reflectDir = reflect(-lightDir, norm);

float 
	diff = max(dot(norm, lightDir), 0.0f),
	spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
vec3 
	ambient = light.ambient * material.ambient,
	diffuse = light.diffuse  * (diff * material.diffuse),
	specular = light.specular * (spec * material.specular),
	result = ambient + diffuse + specular;

color = vec4(result, 1.0f);
}
