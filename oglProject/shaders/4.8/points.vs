#version 460 core

layout(location = 0) in vec3 positions;

uniform mat4
    projection,
    view, 
    model;

void main(){
    gl_Position = projection * view * model * vec4(positions, 1.0);
    gl_PointSize = gl_Position.z;
}