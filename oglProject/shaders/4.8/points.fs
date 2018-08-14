#version 460 core

out vec4 color;
layout(depth_greater) out float gl_FragDepth;

void main(){
    color = vec4(0.5, 0.5, 0.5, 1.0);
    gl_FragDepth = gl_FragCoord.z + 0.01;
}