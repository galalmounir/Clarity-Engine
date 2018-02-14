#version 410 core

in vec3 myColor;
out vec4 frag_colour;

void main() {
    frag_colour = vec4(myColor, 1.0);
}

