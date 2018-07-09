#version 460 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 inTexCoords;

out vec2 TexCoords;
uniform mat4 
	model, view, projection;

void main(){
	TexCoords = inTexCoords;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}