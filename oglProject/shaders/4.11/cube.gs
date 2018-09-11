#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec3 normal;
    vec2 textureCoord;
}gs_in[];

out GS_OUT{
    vec3 normal;
    vec2 textureCoord;
}gs_out;

uniform float time;

vec3 getNormal(){
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}
vec4 explode(vec4 position, vec3 normal){
    float magnitude = 20.0;
    float magnitude1 = 0.5;
    float speed = ( (sin(time * 0.5) + 1.0)/2.0 );
    float speed1 = sin(time * 0.15);
    vec3 direction = normal * speed * magnitude;   
    vec3 direction1 = normal * speed1 * magnitude1;
    return position + vec4(direction, 0.0);
}

vec4 center(vec4 position1, vec4 position2){
    float x = (position1.x + position2.x)/2;
    float y = (position1.y + position2.y)/2;
    float z = (position1.z + position2.z)/2;
    float w = position1.w;
    return vec4(x, y, z, w);
}

void main(){
    // vec3 normal = getNormal();

    // gl_Position = explode(gl_in[0].gl_Position, normal);
    // gs_out.textureCoord = gs_in[0].textureCoord;
    // gs_out.normal = gs_in[0].normal;
    // EmitVertex();
    // gl_Position = explode(gl_in[1].gl_Position, normal);
    // gs_out.textureCoord = gs_in[1].textureCoord;
    // gs_out.normal = gs_in[1].normal;    
    // EmitVertex();
    // gl_Position = explode(gl_in[2].gl_Position, normal);
    // gs_out.textureCoord = gs_in[2].textureCoord;
    // gs_out.normal = gs_in[2].normal;    
    // EmitVertex();
    // EndPrimitive();

    gl_Position = gl_in[0].gl_Position * 2;
    gs_out.textureCoord = gs_in[0].textureCoord;
    gs_out.normal = gs_in[0].normal;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position * 2;
    gs_out.textureCoord = gs_in[1].textureCoord;
    gs_out.normal = gs_in[1].normal;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position * 2;
    gs_out.textureCoord = gs_in[2].textureCoord;
    gs_out.normal = gs_in[2].normal;
    EmitVertex();
    EndPrimitive();

    // gl_Position = gl_in[0].gl_Position;
    // gs_out.textureCoord = gs_in[0].textureCoord;
    // gs_out.normal = gs_in[0].normal;
    // EmitVertex();
    // gl_Position = gl_in[1].gl_Position;
    // gs_out.textureCoord = gs_in[1].textureCoord;
    // gs_out.normal = gs_in[1].normal;
    // EmitVertex();
    // gl_Position = gl_in[2].gl_Position;
    // gs_out.textureCoord = gs_in[2].textureCoord;
    // gs_out.normal = gs_in[2].normal;
    // EmitVertex();
    // EndPrimitive();
}