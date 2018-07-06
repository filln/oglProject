#version 460 core

in vec2 TexCoords;
in vec3 
	Normal, FragPos;
out vec4 outColor;

struct Material{
  	sampler2D 
		texture_diffuse1,
		texture_specular1;
	float shininessTex;
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
#define dirLightsCount 1
#define pointLightsCount 1
#define spotLightsCount 1
uniform	DirLight dirLights[dirLightsCount];
uniform PointLight pointLights[pointLightsCount]; 
uniform	SpotLight spotLights[spotLightsCount];
uniform	vec3 viewPos;

vec3
	calcDirLight(DirLight dirLight, Material material, vec3 norm, vec3 viewDir),
	calcPointLight(PointLight pointLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos),
	calcSpotLight(SpotLight spotLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos);

//float zNear = 0.1, zFar = 100.0;
//float linearizeDepth(float depth){
//	float z = depth*2.0 - 1.0;
//	return (2.0 * zNear * zFar)/(zFar + zNear - z*(zFar - zNear));
//}
void main(){
	vec3 
		norm = normalize(Normal),
		viewDir = normalize(viewPos - FragPos),
		result;

	for(int i = 0; i < dirLightsCount; ++i)
		result += calcDirLight(dirLights[i], material, norm, viewDir);	
	for(int i = 0; i < pointLightsCount; ++i)
		result += calcPointLight(pointLights[i], material, norm, viewDir, FragPos);		
//	for(int i = 0; i < spotLightsCount; ++i)
//		result += calcSpotLight(spotLights[i], material, norm, viewDir, FragPos);	

	outColor = vec4(result, 1.0f);

//	float depth = linearizeDepth(gl_FragCoord.z)/zFar;
//	outColor = vec4(vec3(depth), 1.0f);
	//outColor = vec4(vec3(gl_FragCoord.z), 1.0f);
}

vec3 calcDirLight(DirLight dirLight, Material material, vec3 norm, vec3 viewDir){
	vec3 lightDir = normalize(dirLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);

	vec3 
		ambient = dirLight.ambient * vec3(texture(material.texture_diffuse1, TexCoords)),
		diffuse = dirLight.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)),
		specular = dirLight.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	return (ambient + diffuse + specular);	
}

vec3 calcPointLight(PointLight pointLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos){
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);

	vec3 
		ambient = pointLight.ambient * vec3(texture(material.texture_diffuse1, TexCoords)),
		diffuse = pointLight.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)),
		specular = pointLight.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	float 
		distance = length(pointLight.position - FragPos),
		attenuation = 1.0f/(pointLight.constant + pointLight.linear*distance + pointLight.quadratic*(distance*distance));

	return ( attenuation * (ambient+diffuse+specular) );
}

vec3 calcSpotLight(SpotLight spotLight, Material material, vec3 norm, vec3 viewDir, vec3 FragPos){
	vec3 lightDir = normalize(spotLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininessTex);

	vec3 
		ambient = spotLight.ambient * vec3(texture(material.texture_diffuse1, TexCoords)),
		diffuse = spotLight.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)),
		specular = spotLight.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	float 
		theta = dot(lightDir, normalize(-spotLight.direction)),
		epsilon = spotLight.cutOff - spotLight.outerCutOff,
		intensity = clamp((theta - spotLight.outerCutOff)/epsilon, 0.0f, 1.0f),
		distance = length(spotLight.position - FragPos),
		attenuation = 1.0f/(spotLight.constant + spotLight.linear*distance + spotLight.quadratic*(distance*distance));

	return ( attenuation * (ambient + intensity*(diffuse+specular)) );
}































































