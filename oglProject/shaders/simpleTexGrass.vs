#version 460 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 inTexCoords;

out vec2 TexCoords;
layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main(){
	TexCoords = inTexCoords;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}