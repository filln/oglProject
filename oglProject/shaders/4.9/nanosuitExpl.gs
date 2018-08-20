#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec2 texCoords;
    vec3 normal;
} gs_in[];
out GS_OUT{
    vec2 texCoords;
} gs_out;

uniform float time;

vec3 getNormal(){
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}
vec4 explode(vec4 position, vec3 normal){
    float magnitude = 20.0;
    vec3 direction = normal * ( (sin(time * 0.5) + 1.0)/2.0 ) * magnitude;
    return position + vec4(direction, 0.0);
}

void main(){
    //vec3 normal = getNormal();
    vec3 normal = gs_in[0].normal;

    gl_Position = explode(gl_in[0].gl_Position, normal);
    gs_out.texCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    gs_out.texCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    gs_out.texCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
}