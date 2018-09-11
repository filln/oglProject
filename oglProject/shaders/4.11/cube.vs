#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;

out VS_OUT{
    vec3 normal;
    vec2 textureCoord;
}vs_out;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main(){
    // mat4 normalMatrix = mat4(mat3(transpose(inverse(model))));
    // mat4 pv = projection * view;
    // vs_out.normal = normalize(pv * normalMatrix * vec4(normal, 0.0f));
    vs_out.textureCoord = textureCoord;
    gl_Position = projection * view * model * vec4(position, 1.0);
}