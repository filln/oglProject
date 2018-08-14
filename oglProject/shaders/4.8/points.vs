#version 460 core

layout(location = 0) in vec3 positions;
layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main(){
    gl_Position = projection * view * model * vec4(positions, 1.0);
    gl_PointSize = gl_Position.z;
}