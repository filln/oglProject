#version 460 core

in vec3
    Position,
    Normal;

uniform vec3 cameraPosition;
uniform samplerCube inTexture;

out vec4 color;
void main(){
    vec3 I = normalize(Position - cameraPosition);
    vec3 R = reflect(I, normalize(Normal));
    color = vec4(texture(inTexture, R).rgb, 1.0);
}

