#version 130
//the fragment shader operats on each pixen in a given polygon

in vec4 fragmentColor;

out vec4 color;

void main() {
     color = fragmentColor;
}