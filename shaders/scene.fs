#version 400 core
in vec2 texCoords;
out vec4 FragColor;
uniform sampler2D mtexture;
void main(){
    vec4 pixColor = texture(mtexture, texCoords);
    FragColor = pixColor;
}