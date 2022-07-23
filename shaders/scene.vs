#version 400 core
in vec3 aPos;
in vec2 aTex;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(){
    texCoords = aTex;
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}