#version 460 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;
layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

out vec2 fTexCoords;

void main(){
    fTexCoords = texCoords;
    gl_Position = projection * view * model * vec4(position, 1.0);
}