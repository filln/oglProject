#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 offset;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};

uniform float translationsSize;

out vec3 fColor;

void main(){
    vec2 position1 = position * (gl_InstanceID / translationsSize);
    gl_Position = projection * view * vec4(position1 + offset, 0.0, 1.0);
    fColor = color;
}