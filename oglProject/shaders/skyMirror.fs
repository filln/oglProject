#version 460 core

in vec3
    Position,
    Normal;

out vec4 color;

uniform samplerCube inTexture;
uniform vec3 cameraPosition;

void main(){
    vec3 I = normalize(Position - cameraPosition);
    vec3 R = reflect(I, normalize(Normal));
    color = vec4(texture(inTexture, R).rgb, 1.0);
}

