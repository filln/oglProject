#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 inTexCoords;

out vec2 TexCoords;
out vec3 
	Normal, FragPos;
layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main(){
Normal = mat3(transpose(inverse(model))) * normal;
FragPos = vec3(model * vec4(position, 1.0f));
TexCoords = inTexCoords;
gl_Position = projection * view * model * vec4(position, 1.0f);
}