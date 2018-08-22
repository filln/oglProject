#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out VS_OUT{
    vec3 normal;
} vs_out;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main(){
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * normal, 0.0)));
//    vs_out.normal = normalize(vec3(projection * vec4(normal, 0.0)));
//    vs_out.normal = normalize(vec3(vec4(normalMatrix * normal, 0.0)));
//    vs_out.normal = normalize(normal);
//    vs_out.normal = vec3(projection * vec4(normalMatrix * normal, 0.0));
    gl_Position = projection * view * model * vec4(position, 1.0);
}