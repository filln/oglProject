#version 460 core

in vec2 texCoords;
out vec4 outColor;
uniform sampler2D inTexture;

const float offset = 1.0 / 500.0;
const int size = 9;
void main(){
//////
    vec2 offsets[size] = vec2[](
        vec2(-offset,  offset), vec2( 0.0f,  offset), vec2( offset,  offset),
        vec2(-offset,  0.0f  ), vec2( 0.0f,  0.0f  ), vec2( offset,  0.0f  ),
        vec2(-offset, -offset), vec2( 0.0f, -offset), vec2( offset, -offset)   
    );

    // float kernel[size] = float[](
    //     -1, -1, -1,
    //     -1,  9, -1,
    //     -1, -1, -1
    // );

    // float kernel[size] = float[](
    // 1.0 / 16, 2.0 / 16, 1.0 / 16,
    // 2.0 / 16, 4.0 / 16, 2.0 / 16,
    // 1.0 / 16, 2.0 / 16, 1.0 / 16  
    // );

    float kernel[size] = float[](
        1,  1, 1,
        1, -8, 1,
        1,  1, 1
    );    

    vec3 color = vec3(0.0);
    for(int i = 0; i < size; i++)
        color += vec3(texture(inTexture, texCoords.st + offsets[i])) * kernel[i];
    outColor = vec4(color, 1.0);
//////
//     outColor = texture(inTexture, texCoords);
//     float average = 0.2126 * outColor.r + 0.7152 * outColor.g + 0.0722 * outColor.b;
//     outColor = vec4(average, average, average, 1.0);
//////
//     outColor = vec4(vec3(1.0 - texture(inTexture, texCoords)), 1.0);
}