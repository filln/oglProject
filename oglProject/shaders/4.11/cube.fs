#version 460 core

in GS_OUT{
    vec3 normal;
    vec2 textureCoord;
}fs_in;

out vec4 FragColor;

void main(){
    FragColor = vec4(fs_in.normal, 1.0) + vec4(fs_in.textureCoord, 1.0, 1.0);
}