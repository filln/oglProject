#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};

out vec3 fColor;

uniform vec2 offsets[900];
void main(){
    vec2 offset = offsets[gl_InstanceID];
    gl_Position = projection * view * vec4(position + offset, 0.0, 1.0);
    fColor = color;
}