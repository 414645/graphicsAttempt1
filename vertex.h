#pragma once

#include "GL/glew.h"

  struct Position {
    float x;
    float y;
  };

  struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
  };

struct Vertex {
  //x y position
  Position position;

  //4 bytes for r g b a color
  Color color;
};
