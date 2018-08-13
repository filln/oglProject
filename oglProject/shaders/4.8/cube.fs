#version 460 core

out vec4 color;

void main(){
    if(gl_FrontFacing){
        // if(gl_FragCoord.x < 500)
        //     color = vec4(1.0, 0.0, 0.0, 1.0);
        // else
            color = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else color = vec4(1.0, 1.0, 0.0, 1.0);
}