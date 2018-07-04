#version 460 core

in vec3 
	Normal, FragPos;
in vec2 TexCoords;
out vec4 color;

struct Material{
	vec3
		ambient,
		diffuse,
		specular;
	sampler2D 
		diffuseTex,
		specularTex;
	float 
		shininess,
		shininessTex;
};

struct DirLight{
	vec3 
		direction,
		ambient,
		diffuse,
		specular;
};

struct PointLight{
	vec3 
		position,
		ambient,
		diffuse,
		specular;
	float 
		constant,
		linear,
		quadratic;
};

struct SpotLight{
	vec3 
		direction,
		position,
		ambient,
		diffuse,
		specular;
	float 
		constant,
		linear,
		quadratic,
		cutOff,
		outerCutOff;
};

uniform Material material;
#define pointLightCount 4
uniform PointLight pointLights[pointLightCount]; 
uniform	DirLight dirLight;
uniform	SpotLight spotLight;
uniform	vec3 viewPos;


vec3
	calcDirLight(DirLight dirLight, Material material, vec3 norm, vec3 viewDir, bool isTex),
	calcPointLight(PointLight pointLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos, bool isTex),
	calcSpotLight(SpotLight spotLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos, bool isTex);

void main(){
	vec3 
		norm = normalize(Normal),
		viewDir = normalize(viewPos - FragPos),
		result;
	bool isTex = true;

	result += calcDirLight(dirLight, material, norm, viewDir, isTex);
	for(int i = 0; i < pointLightCount; ++i)
		result += calcPointLight(pointLights[i], material, norm, viewDir, FragPos, isTex);		
	result += calcSpotLight(spotLight, material, norm, viewDir, FragPos, isTex);

	color = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight dirLight, Material material, vec3 norm, vec3 viewDir, bool isTex){
	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec;
	if(isTex)
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);
	else
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 
		ambient,
		diffuse,
		specular;

	if(isTex){
		ambient = dirLight.ambient * vec3(texture(material.diffuseTex, TexCoords));
		diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuseTex, TexCoords));
		specular = dirLight.specular * spec * vec3(texture(material.specularTex, TexCoords));
	}
	else{
		ambient = dirLight.ambient * material.ambient;
		diffuse = dirLight.diffuse * diff * material.diffuse;
		specular = dirLight.specular * spec * material.specular;
	}

	return (ambient + diffuse + specular);	
}

vec3 calcPointLight(PointLight pointLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos, bool isTex){
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec;
	if(isTex)
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);
	else
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 
		ambient,
		diffuse,
		specular;

 	if(isTex){
		ambient = pointLight.ambient * vec3(texture(material.diffuseTex, TexCoords));
		diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuseTex, TexCoords));
		specular = pointLight.specular * spec * vec3(texture(material.specularTex, TexCoords));
	}
	else{
		ambient = pointLight.ambient * material.ambient;
		diffuse = pointLight.diffuse * diff * material.diffuse;
		specular = pointLight.specular * spec * material.specular;
	}

	float 
		distance = length(pointLight.position - FragPos),
		attenuation = 1.0f/(pointLight.constant + pointLight.linear*distance + pointLight.quadratic*(distance*distance));

	return ( attenuation * (ambient+diffuse+specular) );
}

vec3 calcSpotLight(SpotLight spotLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos, bool isTex){
	vec3 lightDir = normalize(spotLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec;
	if(isTex)
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);
	else
		spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 
		ambient,
		diffuse,
		specular;

	if(isTex){
		ambient = spotLight.ambient * vec3(texture(material.diffuseTex, TexCoords));
		diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuseTex, TexCoords));
		specular = spotLight.specular * spec * vec3(texture(material.specularTex, TexCoords));
	}
	else{
		ambient = spotLight.ambient * material.ambient;
		diffuse = spotLight.diffuse * diff * material.diffuse;
		specular = spotLight.specular * spec * material.specular;
	}

	float 
		theta = dot(lightDir, normalize(-spotLight.direction)),
		epsilon = spotLight.cutOff - spotLight.outerCutOff,
		intensity = clamp((theta - spotLight.outerCutOff)/epsilon, 0.0f, 1.0f),
		distance = length(spotLight.position - FragPos),
		attenuation = 1.0f/(spotLight.constant + spotLight.linear*distance + spotLight.quadratic*(distance*distance));

	return ( attenuation * (ambient + intensity*(diffuse+specular)) );
}































































