#include "sprite.h"
#include <iostream>
#include "GL/glew.h"
#include "vertex.h"

#include <cstddef>

using namespace std;

sprite::sprite() {
  _vboID = 0;
}


sprite::~sprite() {
  if (_vboID != 0) {
    glDeleteBuffers(1, &_vboID);
  }
}

void sprite::init(float x, float y,
		  float width, float height) {
  _x = x;
  _y = y;
  _width = width;
  _height = height;

  if (_vboID == 0) {
    glGenBuffers(1, &_vboID);
  }

  //6 vertecies *2 for xy
  Vertex vertexData[6];
  
  //first triangle
  vertexData[0].position.x = x + width;
  vertexData[0].position.y = y + height;
  
  vertexData[1].position.x = x;
  vertexData[1].position.y = y + height;
  
  vertexData[2].position.x = x;
  vertexData[2].position.y = y;
  //second triangle
  vertexData[3].position.x = x;
  vertexData[3].position.y = y;
  
  vertexData[4].position.x = x + width;
  vertexData[4].position.y = y;
  
  vertexData[5].position.x = x + width;
  vertexData[5].position.y = y + height;

  //color for all =  something 
  for (int i = 0; i < 6; i++) {
    vertexData[i].color.r = 255;
    vertexData[i].color.g = 0;
    vertexData[i].color.b = 255;
    vertexData[i].color.a = 255;
  }
  
  //tell opengl to bing our vertex buffer object 
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  //upload it to the GPU
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData),
	       vertexData, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
}

void sprite::draw() {
  //bind buffer object
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);

  //tell opengl we want to use first atribute array
  glEnableVertexAttribArray(0);

  //this is position attibute pointer
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, position));
  //this is color attrib pointer  
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
			sizeof(Vertex), (void*)offsetof(Vertex, color));
  
  
  //draw the 6 verticies to screen
  glDrawArrays(GL_TRIANGLES, 0, 6);

  //disable vertx attrib array (not optional)
  glDisableVertexAttribArray(0);

  //unbind the VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
