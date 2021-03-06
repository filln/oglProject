#version 460 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
//out vec3 ourColor;
out vec2 TexCoord;

layout(std140, binding = 0) uniform matrices{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main() {
gl_Position = projection * view * model * vec4(position, 1.0f);
//ourColor = color;
TexCoord = texCoord;
}
