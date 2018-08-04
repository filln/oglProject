#version 460 core

in vec3
    Position,
    Normal;

uniform float
    material1,
    material2;
uniform vec3 cameraPosition;
uniform samplerCube inTexture;

out vec4 color;
void main(){
    float ratio1 = material1 / material2;
 //   float ratio2 = material2 / material1;
    vec3 I = normalize(Position - cameraPosition);
    vec3 R1 = refract(I, normalize(Normal), ratio1);
 //   vec3 R2 = refract(R1, normalize(Normal), ratio2);
    color = vec4(texture(inTexture, R1).rgb, 1.0);
}