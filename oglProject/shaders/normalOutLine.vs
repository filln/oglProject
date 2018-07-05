#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 inTexCoords;

out vec2 TexCoords;
uniform mat4 
	model, view, projection;
uniform float rate;

void main(){
	TexCoords = inTexCoords;
	gl_Position = projection * view * model * vec4(position + normal * rate, 1.0f);
}