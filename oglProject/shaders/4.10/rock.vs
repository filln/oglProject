#version 460 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in mat4 instanceMatrix;
layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};

out vec2 fTexCoords;

void main(){
    fTexCoords = texCoords;
    gl_Position = projection * view * instanceMatrix * vec4(position, 1.0);
}