#version 130
//The vertex shader operates on each vertex

//input data form the VBO, Each vertex is two floats
in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main() {
     //set x,y position on screen
     gl_Position.xy = vertexPosition;
     //set z position (none since 2d)
     gl_Position.z = 0;
     
     //Indicate theat the cordinates are normalized
     gl_Position.w = 1;

     fragmentColor = vertexColor;
}