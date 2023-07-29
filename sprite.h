#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "GL/glew.h"

class sprite {
 public:
  sprite();
  ~sprite();

  void init(float x, float y,
	    float width, float height);

  void draw();

 private:
  float _x;
  float _y;
  float _width;
  float _height;
  //unsigned int that is 32 bits
  GLuint _vboID;
};

#endif
