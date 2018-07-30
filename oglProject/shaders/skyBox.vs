#version 460 core

layout (location = 0) in vec3 pos;
out vec3 texCoords;
uniform mat4 projection;
uniform mat4 view;

void main(){
    texCoords = pos;
    vec4 posTmp = projection * view * vec4(pos, 1.0);
    gl_Position = posTmp.xyww;
}