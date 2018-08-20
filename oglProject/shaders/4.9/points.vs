#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

out VS_OUT{
    vec3 color;
} vs_out;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.color = color;
}